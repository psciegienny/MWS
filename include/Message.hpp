#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <boost/asio.hpp>
/**
* @details Klasa odpowiedzialna za poprawne informacje o wiadomości
* @author Paweł Ściegienny
* @brief Przesyłana wiadomość.
*/

class Message
{
public:
  ///@brief maksymalna długość nagłówka
  enum { header_length = 4 };
  ///@brief maksymalna długość wiadomości
  enum { max_body_length = 512 };
  ///@brief Konstruktor
  ///@details Konstruktor domyślny - inicjalizuje długość wiadomości 
  Message(): _body_length(0){
  }
  Message(const Message& src){
    std::memcpy(_data, src.data(), src.length());
    _src=src.source();
    _body_length=src.body_length();
    
  }
  ///@brief metoda zwracająca treść wiadomości razem z nagłówkiem
  const char* data() const {
    return _data;
  }
  ///@brief metoda zwracająca treść wiadomości razem z nagłówkiem
  char* data(){
    return _data;
  }
  ///@brief metoda zwracająca długość wiadomości
  ///@details   metoda zwracająca długość wiadomości WRAZ z długością nagłówka
  size_t length() const{
    return header_length + _body_length;
  }
  ///@brief metoda zwracająca treść wiadomości
  const char* body() const{
    return _data + header_length;
  }
  ///@brief metoda zwracająca treść wiadomości
  char* body(){
    return _data + header_length;
  }
  ///@brief metoda zwracająca długość treści
  size_t body_length() const{
    return _body_length;
  }
  ///@brief metoda zwracająca długość treści
  void body_length(size_t length){
    _body_length = length;
    if (_body_length > max_body_length)
      _body_length = max_body_length;
  }
  ///@brief metoda odczytująca nagłówek
  bool decode_header(){
    using namespace std; // For strncat and atoi.
    char header[header_length + 1] = "";
    strncat(header, _data, header_length);
    _body_length = atoi(header);
    if (_body_length > max_body_length){
      _body_length = 0;
      return false;
    }
    return true;
  }
  ///@brief metoda zapisująca nagłówek
  void encode_header(){
    using namespace std; // For sprintf and memcpy.
    char header[header_length + 1] = "";
    sprintf(header, "%4d", (int)_body_length);
    memcpy(_data, header, header_length);
  }
  void source(unsigned src){
      _src=src;
  }
  unsigned source() const{
      return _src;
  }

private:
  unsigned _src;
  char _data[header_length + max_body_length];
  size_t _body_length;
};

#endif // MESSAGE_HPP
