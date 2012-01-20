#ifndef SOCKETSINGLETON_HPP
#define SOCKETSINGLETON_HPP

#include <boost/asio.hpp>

class SocketSingleton {
	
	public:
		static boost::asio::io_service* get();

	private:
		static bool is;
		static boost::asio::io_service* _io_service;
		
};

#endif //SOCKETSINGLETON_HPP
