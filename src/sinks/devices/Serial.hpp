//
//  Serial.hpp
//  Ellydeez
//
//  Created by Pascal Baltazar on 13/07/2018.
//

#ifndef Serial_hpp
#define Serial_hpp

#include <stdio.h>
#include "ofMain.h"
#include "ofxIO.h"
#include "ofxXmlPoco.h"
#include "ofxSerial.h"
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
        
        ~Serial() = default;
        
        void setup(){
            if (name == "") {
                ofLogError("Serial device") << "please set dev name before setup()";
                return;
            }
            if ( !dev.setup(name) )
                ofLogError("Serial device") << "Can't connect to " << name;
        }
        
        void reconnect(){
            if ( !dev.setup(name) )
                ofLogError("Serial device") << "Can't connect to " << name;
        }
        

    protected:
        
        void sendPacket(ofx::IO::ByteBuffer& packet);
        
        ofx::IO::PacketSerialDevice_<ofx::IO::SLIPEncoding, ofx::IO::SLIPEncoding::END, 16384> dev;
        
        std::string name;
        std::string portName(int SN);
        
        
                        
    private:
                        
        void send(ofx::IO::ByteBuffer m) {dev.send(m);}

    };
    
    // Helper functions:
    
    void printSerialDevices();
    

    
} // namespace Sink

#endif /* Serial_hpp */
