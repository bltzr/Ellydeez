//
//  OSCDevice.hpp
//  Ellydeez
//
//  Created by Pascal Baltazar on 14/07/2018.
//

#ifndef OSCDevice_hpp
#define OSCDevice_hpp

#include <stdio.h>
#include "ofxOsc.h"
#include "Serial.hpp"

namespace Sinks {
    
class OSCDevice : public Sinks::Serial {
   
public:
    
    OSCDevice(std::string addr):
    Serial(addr)
    {}
    
    OSCDevice(int SN):
    Serial(SN)
    {}
    
protected:
    
    void sendValueAsIntMessage  (std::string addr, int value);
    void sendPixelsAsBlobMessage(std::string addr, ofPixels& pix, int nBytes);
    
    std::vector<ofxOscMessage> OSCmessages;
    
    void appendOSCMessage(osc::OutboundPacketStream& packet,
                          ofxOscMessage& message);
    
    void sendOSCBundle();
    
};
    
} //namespace Sinks

#endif /* OSCDevice_hpp */
