//
//  Serial.cpp
//  Ellydeez
//
//  Created by Pascal Baltazar on 13/07/2018.
//

#include "Serial.hpp"

namespace Sinks {

string Serial::portName(int SN)
{
    vector<ofx::IO::SerialDeviceInfo> devicesInfo = ofx::IO::SerialDeviceUtils::listDevices();
    for (const ofx::IO::SerialDeviceInfo& devInfo : devicesInfo){
        ofLog() << "for " << devInfo.getHardwareId() << ": " << (to_string(SN)) << " -> find: " << devInfo.getHardwareId().find((to_string(SN))) << endl;
        if ((devInfo.getHardwareId().find((to_string(SN))))<60){
            ofLog() << "found: " << devInfo.getPort() << endl;
            return devInfo.getPort();
        }
    }
    return "";
}

void Serial::sendPacket(ofx::IO::ByteBuffer& packet){
    
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
}

} //namespace Sinks
