#include "Participant.hpp"
#include "Room.hpp"
#include "Message.hpp"
#include "Session.hpp"
#include "Server.hpp"
#include "Client.hpp"
#include <cstdlib>
#include <iostream>
#include <string>



int main(int argc, char** argv){
Server* s;
try
  {
   boost::asio::io_service io_service_server;
    unsigned port;
    if (argc < 2)
        port=1234;
    else 
	port=std::atoi(argv[1]);
    tcp::endpoint endpoint(tcp::v4(), port);
    s = new Server(io_service_server, endpoint); 
    boost::thread server_t(boost::bind(&boost::asio::io_service::run, &io_service_server));
    while(true){
         Message msg = s->receive();
         s->send(msg.source(),"I ACCEPT CHALLANGE");
    }
    server_t.join();

  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }

return 0;
}
