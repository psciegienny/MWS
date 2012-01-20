#include "Worker.hpp"

std::string Worker::execute(std::string s, std::string params){
           std::cout << "EXECUTUJE: "<< s << std::endl;
           return _executor->exec(params);
      } 
      
void Worker::setExecutor(Executor* nowy) {
		  if (_executor != NULL)
			  delete _executor;
		  _executor = nowy;
	  }
 
