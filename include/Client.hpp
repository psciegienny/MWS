#ifndef CLIENT_HPP
#define CLIENT_HPP
#include <cstdlib>
#include <deque>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include "Message.hpp"
#include "SocketSingleton.hpp"
#include "mainwindow.h"
using boost::asio::ip::tcp;

typedef std::deque<Message> Message_queue;
class MainWindow;

/**
* @details Klasa odpowiedzialna za obsługę połączenia z serwerem
* @author Paweł Ściegienny
* @brief Połączenie z serwerem.
*/

//class MainWindow;
class Client{
public:
    void setWindow(MainWindow* w){
        _window=w;
    }
  static Client* getInstance(std::string host="localhost", std::string port="1234");
  ///@brief metoda zamykająca połączenie
  ///@detail metoda binduje handler do_close z metodą post socketu
  
  void close();
  void send(const std::string& m);

private:
  ///@brief Konstruktor połączenia
  ///@defails Konstruktor. Ustawia handler połączenia.
  ///@param[in] io_service referencja do obiektu boost::asio:io_service reprezentującego swego rodzaju socket
  ///@param[in] endpoint_iterator tcp::resolver::iterator wskazujący na hostname i port
  Client(boost::asio::io_service& io_service, tcp::resolver::iterator endpoint_iterator);
  
  ///@brief Konstruktor połączenia
  ///@defails Konstruktor. Ustawia handler połączenia.
  ///@param[in] host hostname
  ///@param[in] ip adres ip
  Client(boost::asio::io_service& io_service, const char* host, const char* port);
 
 ~Client();
  ///@brief metoda wysyłająca wiadomość
  ///@details metoda bindująca handler do_writer z metodą post socketu
  void write(const Message& msg);
private:
  ///@brief handler łączący
  void handle_connect(const boost::system::error_code& error, tcp::resolver::iterator endpoint_iterator);
  ///@brief handler sczytujący header
  void handle_read_header(const boost::system::error_code& error);
  ///@brief handler sczytujący treść
  void handle_read_body(const boost::system::error_code& error);
  ///@brief handler wysyłający wiadomość
  void do_write(Message msg);
  ///@brief handler wysyłający wiadomość
  void handle_write(const boost::system::error_code& error);
  ///@brief handler zamykający połączenie
  void do_close();

  boost::asio::io_service& _io_service;
  tcp::socket _socket;
  Message _read_msg;
  Message_queue _write_msgs;
  boost::thread* _t;
  static Client* _instance;
  static bool is;
  MainWindow* _window;
};

#endif //CLIENT_HPP
