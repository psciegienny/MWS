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

int choose;
Server* s;

std::cout << "0 - client \n 1 - server \n wybor: \n";
std::cin >> choose;

try
  {
///////// TYLE JEŚLI CHODZI O SERVER \\\\\\\\\\

boost::asio::io_service io_service_server;
boost::asio::io_service io_service_client;
char* port;
std::string host="localhost";


    if(choose){
    if (argc < 2)
    {
      std::cerr << "Usage: Server <port>\n";
      return 1;
    }
    port=argv[1];
    tcp::endpoint endpoint(tcp::v4(), std::atoi(port));
    s = new Server(io_service_server, endpoint);  // tak wiem bardzo nieładnie
    }
    boost::thread server_t(boost::bind(&boost::asio::io_service::run, &io_service_server)); 
//\
\\\\\\\\\\\ MAMY SERVER TO TERAZ KLIENT ///////////

    if (argc == 3){
        port=argv[2];
        host=argv[1];
    }

///////////      TEN NAJWAŻNIEJSZY FRAGMENT KLIENCKI                    \\\\\\\\\\\\\ 

    Client c(io_service_client, host.c_str(), port);
    boost::thread client_t(boost::bind(&boost::asio::io_service::run, &io_service_client)); //\
\\\\\\\\\\\     I TERAZ JUŻ TYLKO c.write(Message)                      /////////////


    char line[Message::max_body_length + 1];
    while (std::cin.getline(line, Message::max_body_length + 1))
    {
        c.send(line);
//      using namespace std; // For strlen and memcpy.
//      Message msg;
//      msg.body_length(strlen(line));
//      memcpy(msg.body(), line, msg.body_length());
//      msg.encode_header();
      if(choose) s->send("JOKE");
      if(choose)  std::cout << "\n\nTO JEST Z TODO: " << s->receive().body() << "\n\n\n\n" << std::endl;
//      c.write(msg);*/
    }
    
    c.close();
    server_t.join();
    client_t.join();


  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }

return 0;
}
