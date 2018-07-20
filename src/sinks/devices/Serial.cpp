//
//  SerialDevice.cpp
//  Ellydeez
//
//  Created by Pascal Baltazar on 13/07/2018.
//

#include "Serial.hpp"

namespace Sinks {
namespace Devices {
    
void Serial::setup() {
    if (name == "") {
        ofLogError("Serial device") << "please set dev name before setup()";
        return;
    }
    if ( !dev.setup(name) )
        ofLogError("Serial device") << "Can't connect to " << name;
}

string Serial::portName( int SN )
{
    vector<ofx::IO::SerialDeviceInfo> devicesInfo = ofx::IO::SerialDeviceUtils::listDevices();
    for (const ofx::IO::SerialDeviceInfo& devInfo : devicesInfo){
        // ofLog() << "for " << devInfo.getHardwareId() << ": " << (to_string(SN)) << " -> find: " << devInfo.getHardwareId().find((to_string(SN))) << endl;
        if ((devInfo.getHardwareId().find((to_string(SN))))<60){
            ofLog() << "Serial : found device " << devInfo.getPort() << "for SN " << SN << endl;
            return devInfo.getPort();
        }
    }
    return "";
}

void Serial::sendPacket( const ofx::IO::ByteBuffer& packet ){
    
    try {
        send(packet);
    } catch ( serial::SerialException e) {
        ofLogError("Serial Device") << "failed to send data : " << e.what();
        reconnect();
    }
}

// Helper functions:

void printSerialDevices(){
    
    int devNumb = 0;
    
    vector<ofx::IO::SerialDeviceInfo> devicesInfo = ofx::IO::SerialDeviceUtils::listDevices();
    ofLogNotice("ofApp::setup") << "Connected Devices: ";
    for (ofx::IO::SerialDeviceInfo d : devicesInfo){
        ofLogNotice("  ") << devNumb << ": " << d;
        ++devNumb;
    }
    cout << endl;
}

} //namespace Devices
} //namespace Sinks
