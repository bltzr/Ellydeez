#pragma once

#include "ofMain.h"

#include "ofxSyphon.h"

#include "ledLine.hpp"
#include "DMXLine.hpp"


#define NUM_MSG_STRINGS 20


// project-specific numbers:
#define NUM_TEENSIES 9          // How many Teensies to use ?
#define NUM_LEDLINES 18          // How many physical LED lines ?
#define NUM_DMXLINES 1
#define NUM_SYPHON 1            // How many Syphon clients ?
#define PORTIN 66666            // for incoming OSC messages



//--------------------------------------------------------------
//    Our App

class ofApp : public ofBaseApp {

public:
    void setup();
    void update();
    void draw();

    ofFbo fbo ;
    ofPixels pixels ;

    ofxSyphonClient mClient ;
    int sourceXsize = 0, sourceYsize = 0;
    int drawXsize = 132, drawYsize = 19;

    ofVideoPlayer trame;

    ofxOscReceiver receiver;

    /// TODO: move this in the appropriate class
    std::vector<ofx::IO::SerialDeviceInfo> devicesInfo;
    std::string portName(int SN)
    {
        for (const ofx::IO::SerialDeviceInfo& devInfo : devicesInfo){
            cout << "for " << devInfo.getHardwareId() << ": " << (std::to_string(SN)) << " -> find: " << devInfo.getHardwareId().find((std::to_string(SN))) << endl;
            if ((devInfo.getHardwareId().find((std::to_string(SN))))<60){
                cout << "found: " << devInfo.getPort() << endl;
                return devInfo.getPort();
            }
        }
        return "";
    }
    // ^
    
    OSC2APA102 device[NUM_TEENSIES] ;

    LedLine ledLine[NUM_LEDLINES];
    DMXLine dmxLine[NUM_DMXLINES];
    
    int playing = 0;
    
    
    
    // temporary way to deal with brightness info from the video:
    ofPixels BrightPix;
    unsigned char * Brights;

    


/// TODO: check that we really need this:

    void onSerialBuffer(const ofx::IO::SerialBufferEventArgs& args);
    void onSerialError(const ofx::IO::SerialBufferErrorEventArgs& args);
    std::vector<SerialMessage> serialMessages;


    int current_msg_string;
    string msg_strings[NUM_MSG_STRINGS];
    float timers[NUM_MSG_STRINGS];
    
    
};
