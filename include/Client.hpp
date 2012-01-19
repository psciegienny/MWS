#ifndef CLIENT_HPP
#define CLIENT_HPP
#include <cstdlib>
#include <deque>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include "Message.hpp"

using boost::asio::ip::tcp;

typedef std::deque<Message> Message_queue;

class SocketSingleton{
   public:
   static boost::asio::io_service* get(){
      if(!is){ 
          _io_service=new boost::asio::io_service;
          is=true;
          std::cout << "tworze watek" << std::endl;
          _t = new boost::thread(boost::bind(&boost::asio::io_service::run, _io_service));
      }
      return _io_service;
   }
   static void join(){
       _t->join();
       delete _t;
   }
   private:
   static bool is;
   static boost::asio::io_service* _io_service;
   static boost::thread* _t;
};

boost::asio::io_service* SocketSingleton::_io_service;
boost::thread* SocketSingleton::_t;
bool SocketSingleton::is=false;

/**
* @details Klasa odpowiedzialna za obsługę połączenia z serwerem
* @author Paweł Ściegienny
* @brief Połączenie z serwerem.
*/

class Client{
private:
  ///@brief Konstruktor połączenia
  ///@defails Konstruktor. Ustawia handler połączenia.
  ///@param[in] io_service referencja do obiektu boost::asio:io_service reprezentującego swego rodzaju socket
  ///@param[in] endpoint_iterator tcp::resolver::iterator wskazujący na hostname i port
  Client(boost::asio::io_service& io_service, tcp::resolver::iterator endpoint_iterator)
    : _io_service(io_service), _socket(io_service){
    tcp::endpoint endpoint = *endpoint_iterator;
    _socket.async_connect(endpoint, boost::bind(&Client::handle_connect, this, boost::asio::placeholders::error, ++endpoint_iterator));
  }
  
  ///@brief Konstruktor połączenia
  ///@defails Konstruktor. Ustawia handler połączenia.
  ///@param[in] host hostname
  ///@param[in] ip adres ip
  Client(boost::asio::io_service& io_service, const char* host, const char* port):
   _io_service(io_service), _socket(io_service)
  {
    tcp::resolver resolver(_io_service);
    tcp::resolver::query query(host, port);
    tcp::resolver::iterator iterator = resolver.resolve(query);
    tcp::endpoint endpoint = *iterator;
    _socket.async_connect(endpoint, boost::bind(&Client::handle_connect, this, boost::asio::placeholders::error, ++iterator));
  }
  ~Client(){
     SocketSingleton::join();
  }
  ///@brief metoda wysyłająca wiadomość
  ///@details metoda bindująca handler do_writer z metodą post socketu
  void write(const Message& msg){
    _io_service.post(boost::bind(&Client::do_write, this, msg));
  }
public:
  ///@brief metoda zamykająca połączenie
  ///@detail metoda binduje handler do_close z metodą post socketu
  void close(){
    _io_service.post(boost::bind(&Client::do_close, this));
  }
  void send(const std::string& m){
      Message msg;
      msg.body_length(strlen(m.c_str()));
      memcpy(msg.body(), m.c_str(), msg.body_length());
      msg.encode_header();
      write(msg);
  }
private:
  ///@brief handler łączący
  void handle_connect(const boost::system::error_code& error, tcp::resolver::iterator endpoint_iterator){
    if (!error)
    {
      boost::asio::async_read(_socket,
          boost::asio::buffer(_read_msg.data(), Message::header_length),
          boost::bind(&Client::handle_read_header, this, boost::asio::placeholders::error));
    }
    else if (endpoint_iterator != tcp::resolver::iterator())
    {
      _socket.close();
      tcp::endpoint endpoint = *endpoint_iterator;
      _socket.async_connect(endpoint, boost::bind(&Client::handle_connect, this,
            boost::asio::placeholders::error, ++endpoint_iterator));
    }
  }
  ///@brief handler sczytujący header
  void handle_read_header(const boost::system::error_code& error){
    if (!error && _read_msg.decode_header()){
      boost::asio::async_read(_socket,
          boost::asio::buffer(_read_msg.body(), _read_msg.body_length()),
          boost::bind(&Client::handle_read_body, this, boost::asio::placeholders::error));
    }
    else
      do_close();
  }
  ///@brief handler sczytujący treść
  void handle_read_body(const boost::system::error_code& error){
    if (!error){
      //LET'S DO STH WITH MESSAGE WHICH INCOMED

      // odpalenie metody rysującej?

      std::cout.write(_read_msg.body(), _read_msg.body_length());
      std::cout << "\n";

      // I TO BY BYŁO NA TYLE
      boost::asio::async_read(_socket, boost::asio::buffer(_read_msg.data(), Message::header_length), boost::bind(&Client::handle_read_header, this,
            boost::asio::placeholders::error));
    }
    else
      do_close();
  }
  ///@brief handler wysyłający wiadomość
  void do_write(Message msg)
  {
    bool write_in_progress = !_write_msgs.empty();
    _write_msgs.push_back(msg);
    if (!write_in_progress){
      boost::asio::async_write(_socket,
          boost::asio::buffer(_write_msgs.front().data(),
            _write_msgs.front().length()),
          boost::bind(&Client::handle_write, this,
            boost::asio::placeholders::error));
    }
  }
  ///@brief handler wysyłający wiadomość
  void handle_write(const boost::system::error_code& error)
  {
    if (!error)
    {
      _write_msgs.pop_front();
      if (!_write_msgs.empty())
      {
        boost::asio::async_write(_socket,
            boost::asio::buffer(_write_msgs.front().data(),
              _write_msgs.front().length()),
            boost::bind(&Client::handle_write, this,
              boost::asio::placeholders::error));
      }
    }
    else
    {
      do_close();
    }
  }
  ///@brief handler zamykający połączenie
  void do_close()
  {
    _socket.close();
  }

  boost::asio::io_service& _io_service;
  tcp::socket _socket;
  Message _read_msg;
  Message_queue _write_msgs;
public:
  static Client* getInstance(std::string host="localhost", std::string port="1234"){
      if(!is){
          _instance=new Client(*SocketSingleton::get(), host.c_str(), port.c_str());
          is=true;
      }
      return _instance;
  }
  private:
  static Client* _instance;
  static bool is;
};

bool Client::is= false;
Client* Client::_instance;

#endif //CLIENT_HPP
