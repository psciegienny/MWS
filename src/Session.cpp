#include "Session.hpp"
  void Session::start(){
    _room.join(shared_from_this());
    boost::asio::async_read(_socket, boost::asio::buffer(_read_msg.data(), Message::header_length),
        boost::bind(&Session::handle_read_header, shared_from_this(), boost::asio::placeholders::error));
  }

  void Session::deliver(const Message& msg){
    bool write_in_progress = !_write_msgs.empty();
    
    _write_msgs.push_back(msg);
    if (!write_in_progress)
    {
      boost::asio::async_write(_socket, boost::asio::buffer(_write_msgs.front().data(),_write_msgs.front().length()),
          boost::bind(&Session::handle_write, shared_from_this(), boost::asio::placeholders::error));
    }
  }

  void Session::handle_read_header(const boost::system::error_code& error){
    if (!error && _read_msg.decode_header()){
      boost::asio::async_read(_socket, boost::asio::buffer(_read_msg.body(), _read_msg.body_length()),
          boost::bind(&Session::handle_read_body, shared_from_this(), boost::asio::placeholders::error));

    }
    else
      _room.leave(shared_from_this());

  }
  void Session::handle_read_body(const boost::system::error_code& error)
  {
    if (!error){
//      _read_msg.source((void*) &_socket);
      _read_msg.source(_room.search(this));
      _room.todo(_read_msg);
      _room.deliver(_read_msg);
      boost::asio::async_read(_socket, boost::asio::buffer(_read_msg.data(), Message::header_length),
          boost::bind(&Session::handle_read_header, shared_from_this(), boost::asio::placeholders::error));
    }
    else
      _room.leave(shared_from_this());
  }

  void Session::handle_write(const boost::system::error_code& error){
    if (!error){
      _write_msgs.pop_front();
      if (!_write_msgs.empty()){
        boost::asio::async_write(_socket, boost::asio::buffer(_write_msgs.front().data(), _write_msgs.front().length()),
            boost::bind(&Session::handle_write, shared_from_this(), boost::asio::placeholders::error));
      }
    }
    else
      _room.leave(shared_from_this());
  }
