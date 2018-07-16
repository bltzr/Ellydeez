//
//  SerialIn.hpp
//  Ellydeez
//
//  Created by Pascal Baltazar on 14/07/2018.
//

#ifndef SerialIn_hpp
#define SerialIn_hpp

/* // we might need those for serial inputs
 
#define NUM_MSG_STRINGS 20

#include <stdio.h>
#include "ofMain.h"

 using namespace std;

class SerialIn {

    int current_msg_string;
    string msg_strings[NUM_MSG_STRINGS];
    float timers[NUM_MSG_STRINGS];
    
    void onSerialBuffer(const ofx::IO::SerialBufferEventArgs& args);
    void onSerialError(const ofx::IO::SerialBufferErrorEventArgs& args);
    std::vector<SerialMessage> serialMessages;
    

}
 
 
class SerialMessage {
public:
     SerialMessage():
     fade(0) {}
     
     SerialMessage(const string& _message,
     const std::string& _exception,
     int _fade):
     message(_message),
     exception(_exception),
     fade(_fade) {}
     
     string message;
     string exception;
     int fade;
};
*/


#endif /* SerialIn_hpp */
