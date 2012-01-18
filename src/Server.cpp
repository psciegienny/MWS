#include "Server.hpp"
  void Server::handle_accept(Session_ptr session, const boost::system::error_code& error){
    if (!error){
      session->start();
      Session_ptr new_session(new Session(_io_service, _room));
      _acceptor.async_accept(new_session->socket(), boost::bind(&Server::handle_accept, this, new_session, boost::asio::placeholders::error));
    }
  }
