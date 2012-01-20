#include "../include/SocketSingleton.hpp"


boost::asio::io_service* SocketSingleton::_io_service;
bool SocketSingleton::is=false;

boost::asio::io_service* SocketSingleton::get() {
    if(!is) {
        _io_service=new boost::asio::io_service;
        is=true;
    }
    return _io_service;
}

