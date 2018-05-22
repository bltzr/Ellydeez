//
//  OSC2APA102.hpp
//  Ellydee
//
//  Created by Pascal Baltazar on 19/05/2018.
//

#ifndef OSC2APA102_hpp
#define OSC2APA102_hpp

#include "ofxSerial.h"
#include "ofxIO.h"


//--------------------------------------------------------------
//      Our utility classes

class SerialMessage
{
public:
    SerialMessage():
    fade(0) {}
    
    SerialMessage(const std::string& _message,
                  const std::string& _exception,
                  int _fade):
    message(_message),
    exception(_exception),
    fade(_fade) {}
    
    std::string message;
    std::string exception;
    int fade;
};

//--------------------------------------------------------------
class OSC2APA102
{
public:
    ofx::IO::PacketSerialDevice_<ofx::IO::SLIPEncoding, ofx::IO::SLIPEncoding::END, 16384> dev;
    string name;
    
    void setup(){
        if (name == "") {
            ofLogError("OSC2APA102 Teensy") << "please set dev name before setup()";
            return;
        }
        if ( !dev.setup(name) )
            ofLogError("OSC2APA102 Teensy") << "Can't connect to " << name;
    }
};


#endif /* OSC2APA102_hpp */
