#ifndef SERVER_HPP
#define SERVER_HPP

#include "Room.hpp"
#include "Session.hpp"
#include "Message.hpp"
#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <list>

class Server {
	
	public:
		Server(boost::asio::io_service& io_service, const tcp::endpoint& endpoint);
		void handle_accept(Session_ptr session, const boost::system::error_code& error);
		void send(unsigned who, const std::string& m);
		const Message receive();
		
	private:
		boost::asio::io_service& _io_service;
		tcp::acceptor _acceptor;
		Room _room;
		
};

typedef boost::shared_ptr<Server> Server_ptr;
typedef std::list<Server_ptr> Server_list;

#endif //SERVER_HPP
