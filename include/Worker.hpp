/// Zaczynam pracować społecznie, pozdrawiam Paweł Ściegienny
#ifndef WORKER_HPP
#define WORKER_HPP
#include <iostream>
#include <string>
#include <sstream>
#include <cmath>

class Executor{
  public:
      virtual std::string exec(std::string s)=0;
};
class ListExecutor: public Executor{
 public:
    virtual std::string exec(std::string s){
        std::string list = "calkujKwadratowe <a> <b> <A> <B> <C>\ncalkujWielomian <a> <b> <n> <A> <B> <C> (...)";
        return list;
    }
};

class CalkujWielomianExecutor;

class CalkujKwadratoweExecutor: public Executor{
	friend class CalkujWielomianExecutor;
  public:
     virtual std::string exec(std::string s){
          double a, b;
          double A, B, C;
          std::stringstream tmp, res;
          tmp << s;
          tmp >> a;
          tmp >> b;
          tmp >> A;
          tmp >> B;
          tmp >> C;
          double width = (b-a)/100000;
          double f1, f2;
          double wynik = 0;
          for(int i=0; i<100000; ++i){
             f1=A*(a+i*width)*(a+i*width)+B*(a+i*width)+C;
             f2=A*(a+(i+1)*width)*(a+(i+1)*width)+B*(a+(i+1)*width)+C;
             wynik+=width*(f1+f2)/2;
          }
          res << "calkujKwadratowe " << s << ": "<< wynik;
          return res.str(); 
     }  
	private:
		static void obsluz(const std::string& polecenie, Executor** wykonawca) {
			if(polecenie == "calkujKwadratowe")
				*wykonawca = new CalkujKwadratoweExecutor();
			else
				*wykonawca = new ListExecutor();
		}
};
class CalkujWielomianExecutor: public Executor{
  public:
     virtual std::string exec(std::string s){
          double a, b;
          unsigned n;
          double* params;
          std::stringstream tmp, res;
          tmp << s;
          tmp >> a;
          tmp >> b;
          tmp >> n;
          params = new double[n+1];
          for (int i=0; i<n+1; ++i)
              tmp >> params[i];

          double width = (b-a)/100000;
          double f1, f2;
          double wynik = 0;
          for(int i=0; i<100000; ++i){
             f1=f2=0;
             for(int j=0; j<n+1; ++j){
                  std::cout << params[j] << "*x^" << n-j << std::endl;
                  f1+=params[j]*std::pow(a+j*width,n-j);
                  f2+=params[j]*std::pow(a+(j+1)*width,n-j);
             }
             wynik+=width*(f1+f2)/2;
             std::cerr << wynik << std::endl;
          }
          res << "calkujWielomian " << s << ": "<< wynik;
          return res.str(); 
     }
     static void obsluz(const std::string& polecenie, Executor** wykonawca) {
		 if(polecenie == "calkujWielomian")
			 *wykonawca = new CalkujWielomianExecutor();
		 else
			 CalkujKwadratoweExecutor::obsluz(polecenie, wykonawca);
	 }
};
class Worker{
	
  public:
	  Worker() {_executor = NULL;}
      std::string execute(std::string s, std::string params){
           std::cout << "EXECUTUJE: "<< s << std::endl;
           return _executor->exec(params);
      }
      void setExecutor(Executor* nowy) {
		  if (_executor != NULL)
			  delete _executor;
		  _executor = nowy;
	  }
   private:
      Executor* _executor;
};

#endif //WORKER_HPP
