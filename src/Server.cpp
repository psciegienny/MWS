#include "Server.hpp"

  void Server::handle_accept(Session_ptr session, const boost::system::error_code& error){
    if (!error){
      session->start();
      Session_ptr new_session(new Session(_io_service, _room));
      _acceptor.async_accept(new_session->socket(), boost::bind(&Server::handle_accept, this, new_session, boost::asio::placeholders::error));
    }
  }
  
  Server::Server(boost::asio::io_service& io_service, const tcp::endpoint& endpoint): _io_service(io_service), _acceptor(io_service, endpoint){
    Session_ptr new_session(new Session(_io_service, _room));
    _acceptor.async_accept(new_session->socket(), boost::bind(&Server::handle_accept, this, new_session, boost::asio::placeholders::error));
  }

  void Server::send(unsigned who, const std::string& m){
      Message msg;
      msg.body_length(strlen(m.c_str()));
      memcpy(msg.body(), m.c_str(), msg.body_length());
      msg.encode_header();
      _room.deliver(who, msg);      
  }
  
    const Message Server::receive(){
         const Message& tmp = _room.todo();
         return tmp;
     }