#ifndef SOCKETSINGLETON_HPP
#define SOCKETSINGLETON_HPP
class SocketSingleton{
   public:
   static boost::asio::io_service* get(){
      if(!is){
          _io_service=new boost::asio::io_service;
          is=true;
      }
      return _io_service;
   }
   private:
   static bool is;
   static boost::asio::io_service* _io_service;
};

boost::asio::io_service* SocketSingleton::_io_service;
bool SocketSingleton::is=false;

#endif //SOCKETSINGLETON_HPP
