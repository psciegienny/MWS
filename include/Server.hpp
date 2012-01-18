#ifndef SERVER_HPP
#define SERVER_HPP
#include "Room.hpp"
#include "Session.hpp"
#include "Message.hpp"
#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <list>
class Server
{
public:
  Server(boost::asio::io_service& io_service, const tcp::endpoint& endpoint): _io_service(io_service), _acceptor(io_service, endpoint){
    Session_ptr new_session(new Session(_io_service, _room));
    _acceptor.async_accept(new_session->socket(), boost::bind(&Server::handle_accept, this, new_session, boost::asio::placeholders::error));
  }

  void handle_accept(Session_ptr session, const boost::system::error_code& error);
  void send(const std::string& m){
      Message msg;
      msg.body_length(strlen(m.c_str()));
      memcpy(msg.body(), m.c_str(), msg.body_length());
      msg.encode_header();
      _room.deliver(msg);      
  }
  Message& receive(){
         _room.todo();
     }
private:
  boost::asio::io_service& _io_service;
  tcp::acceptor _acceptor;
  Room _room;
};

typedef boost::shared_ptr<Server> Server_ptr;
typedef std::list<Server_ptr> Server_list;





#endif //SERVER_HPP
