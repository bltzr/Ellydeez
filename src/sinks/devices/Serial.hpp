//
//  Serial.hpp
//  Ellydeez
//
//  Created by Pascal Baltazar on 13/07/2018.
//

#ifndef Serial_hpp
#define Serial_hpp

#include <stdio.h>
#include "ofxIO.h"
#include "ofxXmlPoco.h"
#include "SinkBase.hpp"

namespace Sinks {
    
    class Serial : public Sink {
        
    public:
        
        Serial(std::string addr):
            name{addr}
            {setup();}
        
        Serial(int SN):
            name{portName(SN)}
            {setup();}
        
        void send(ofx::IO::ByteBuffer m) {dev.send(m);}
        void reconnect(){
            if ( !dev.setup(name) )
                ofLogError("Serial device") << "Can't connect to " << name;
        }
        
    protected:
        
        ofx::IO::PacketSerialDevice_<ofx::IO::SLIPEncoding, ofx::IO::SLIPEncoding::END, 16384> dev;
        
        std::string name;
        
        void setup(){
            if (name == "") {
                ofLogError("Serial device") << "please set dev name before setup()";
                return;
            }
            if ( !dev.setup(name) )
                ofLogError("Serial device") << "Can't connect to " << name;
        }
        
        std::vector<ofx::IO::SerialDeviceInfo> devicesInfo;
        
        std::string portName(int SN)
        {
            for (const ofx::IO::SerialDeviceInfo& devInfo : devicesInfo){
                ofLog() << "for " << devInfo.getHardwareId() << ": " << (std::to_string(SN)) << " -> find: " << devInfo.getHardwareId().find((std::to_string(SN))) << endl;
                if ((devInfo.getHardwareId().find((std::to_string(SN))))<60){
                    ofLog() << "found: " << devInfo.getPort() << endl;
                    return devInfo.getPort();
                }
            }
            return "";
        }
        
   
        
        
    }; 
    
    /// TODO: check that we really need this:
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
    
} // namespace Sink

#endif /* Serial_hpp */
