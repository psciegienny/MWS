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
try{
boost::asio::io_service io_service_client;
std::string host;
std::string port;
if (argc < 3){
    host="localhost";
    port="1234";
}
      Client* c = Client::getInstance(host, port);
//    Client c(io_service_client, host.c_str(), port.c_str());
    boost::thread client_t(boost::bind(&boost::asio::io_service::run, &io_service_client)); 


    char line[Message::max_body_length + 1];
    while (std::cin.getline(line, Message::max_body_length + 1))
    {
        c->send(line);
    }
    
    c->close();
    client_t.join();


  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }

return 0;
}
