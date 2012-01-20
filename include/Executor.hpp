#ifndef EXECUTOR_HPP
#define EXECUTOR_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <cmath>

class Executor {
	
	public:
		virtual std::string exec(std::string s) = 0;

};

class ListExecutor : public Executor {

	public:
		std::string exec(std::string s);
		
};

class CalkujWielomianExecutor;

class CalkujKwadratoweExecutor : public Executor {
	
	friend class CalkujWielomianExecutor;
	
	public:
		std::string exec(std::string s);
		
	private:
		static void obsluz(const std::string& polecenie, Executor** wykonawca) {
			if(polecenie == "calkujKwadratowe")
				*wykonawca = new CalkujKwadratoweExecutor();
			else
				*wykonawca = new ListExecutor();
		}
		
};

class CalkujWielomianExecutor : public Executor {
  
	public:
		std::string exec(std::string s);
		static void obsluz(const std::string& polecenie, Executor** wykonawca) {
			if(polecenie == "calkujWielomian")
				*wykonawca = new CalkujWielomianExecutor();
			else
				CalkujKwadratoweExecutor::obsluz(polecenie, wykonawca);
		}
		
};

#endif //EXECUTOR_HPP
