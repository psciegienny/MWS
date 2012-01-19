#include "Room.hpp"
#include <sstream>
 void Room::join(Participant_ptr participant){
   _participants.insert(participant);
   _idents.push_back(std::pair<Participant*, unsigned>(participant.get(), _current_id++));
    std::for_each(_recent_msgs.begin(), _recent_msgs.end(),
        boost::bind(&Participant::deliver, participant, _1));
  }

  void Room::leave(Participant_ptr participant){
        _participants.erase(participant);
  }
  void Room::todo(const Message msg){
      std::cout << "pushbackuje message od: " << msg.source() << std::endl;
      _todo.push_back(msg);
  }
  Message Room::todo(){
     while(true){
     if(!_todo.empty()){
       Message msg = _todo.front();
        _todo.pop_front();
        return msg;
        }
     boost::this_thread::sleep(boost::posix_time::milliseconds(500));
     }
  }
  void Room::deliver(const Message& msg){

///poczatek przykladu udupiania czesci pakietow
    std::cout << "od" << msg.source() << std::endl;
    char tmp[512];
    std::memcpy(tmp,msg.body(),msg.body_length());
    tmp[msg.body_length()]='\0';
    std::string body(tmp);
    if(body=="NIEE") return;
///koniec przykladu udupiania czesci pakietow


    _recent_msgs.push_back(msg);
    while (_recent_msgs.size() > max_recent_msgs)
      _recent_msgs.pop_front();
    std::for_each(_participants.begin(), _participants.end(),
        boost::bind(&Participant::deliver, _1, boost::ref(msg)));
  }
  void Room::deliver(unsigned who, const Message& msg){
      search(who)->deliver(msg);
  }

