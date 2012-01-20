/// Zaczynam pracować społecznie, pozdrawiam Paweł Ściegienny
#ifndef WORKER_HPP
#define WORKER_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include "Executor.hpp"

class Worker {
	
	public:
		Worker() { _executor = NULL; }
		std::string execute(std::string s, std::string params);
		void setExecutor(Executor* nowy);
	
	private:
		Executor* _executor;
		
};

#endif //WORKER_HPP
