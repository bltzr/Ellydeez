//
//  SerialDevice.hpp
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

using namespace std;

namespace Sinks {
namespace Devices {
    
class Serial : public Sink {
    
public:
    
    Serial() = default;
    
    Serial(string addr):
        name{addr}
        {setup();}
    
    Serial(int SN):
        name{portName(SN)}
        {setup();}
    
    ~Serial() = default;
    
    void setup() override; 
    
    void setup( string deviceName ) {
        name = deviceName;
        setup();
    }
    
    void setup( int SN) {
        name = portName(SN);
        setup();
    }
    
    void update() override  { cout << "serial updating" << endl;}
    void draw()   override  {}
    void exit()   override  {}
    
    void reconnect(){
        if ( !dev.setup(name) )
            ofLogError("Serial device") << "Can't connect to " << name;
    }

protected:
    
    void sendPacket(const ofx::IO::ByteBuffer& packet);
    
    ofx::IO::PacketSerialDevice_<ofx::IO::SLIPEncoding, ofx::IO::SLIPEncoding::END, 16384>      dev;
    
    string      name;
    string      portName(int SN);
    
    
private:
    
    void send(ofx::IO::ByteBuffer m) {dev.send(m);}

};

// Helper functions:

void printSerialDevices();


} // namespace Devices
} // namespace Sink

#endif /* Serial_hpp */
