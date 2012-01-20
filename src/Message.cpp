 #include "../include/Message.hpp"
 
 Message::Message(): _body_length(0){
      std::memset((void*)_data,0, max_body_length+header_length);
  }
 
 Message::Message(const Message& src){
    std::memset((void*)_data,0, max_body_length+header_length);
//    std::cout << "Konstruktor kopiujacy Message'a" << std::endl;
    std::memcpy(_data, src.data(), src.length());
    _src=src.source();
    _body_length=src.body_length();
    
  }
  
  void Message::operator=(const Message& src){
    std::cout << "operator=" << std::endl;
    std::memcpy(_data, src.data(), src.length());
    _src=src.source();
    _body_length=src.body_length();
  }
  
  void Message::body_length(size_t length){
  _body_length = length;
    if (_body_length > max_body_length)
      _body_length = max_body_length;
  }
  
  bool Message::decode_header(){
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
  
  void Message::encode_header(){
    using namespace std; // For sprintf and memcpy.
    char header[header_length + 1] = "";
    sprintf(header, "%4d", (int)_body_length);
    memcpy(_data, header, header_length);
  }
