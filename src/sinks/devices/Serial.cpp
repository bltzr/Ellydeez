//
//  Serial.cpp
//  Ellydeez
//
//  Created by Pascal Baltazar on 13/07/2018.
//

#include "Serial.hpp"

namespace Sinks {

    std::string Serial::portName(int SN)
    {
        std::vector<ofx::IO::SerialDeviceInfo> devicesInfo = ofx::IO::SerialDeviceUtils::listDevices();
        for (const ofx::IO::SerialDeviceInfo& devInfo : devicesInfo){
            ofLog() << "for " << devInfo.getHardwareId() << ": " << (std::to_string(SN)) << " -> find: " << devInfo.getHardwareId().find((std::to_string(SN))) << endl;
            if ((devInfo.getHardwareId().find((std::to_string(SN))))<60){
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
        
        std::vector<ofx::IO::SerialDeviceInfo> devicesInfo = ofx::IO::SerialDeviceUtils::listDevices();
        ofLogNotice("ofApp::setup") << "Connected Devices: ";
        for (ofx::IO::SerialDeviceInfo d : devicesInfo){
            ofLogNotice("  ") << devNumb << ": " << d;
            ++devNumb;
        }
    }

} //namespace Sinks
