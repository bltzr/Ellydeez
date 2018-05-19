#pragma once

#include "ofMain.h"

#include "ledLine.hpp"

#include "ofxSyphon.h"


#define NUM_MSG_STRINGS 20


// project-specific numbers:
#define NUM_TEENSIES 3          // How many Teensies to use ?
#define NUM_LEDLINES 6          // How many physical LED lines ?
#define NUM_SYPHON 1            // How many Syphon clients ?
#define PORTIN 66666              // for incoming OSC messages



//--------------------------------------------------------------
//    Our App

class ofApp : public ofBaseApp {

	public:
		void setup();
		void update();
		void draw();
    
        ofFbo fbo ;
        ofPixels pixels ; ;
    
        ofxSyphonClient mClient ;
        int sourceXsize = 0, sourceYsize = 0;
        int drawXsize = 0, drawYsize = 0;
    
        ofxOscReceiver receiver;
    
        void onSerialBuffer(const ofx::IO::SerialBufferEventArgs& args);
        void onSerialError(const ofx::IO::SerialBufferErrorEventArgs& args);
  
        OSC2APA102 device[NUM_TEENSIES] ;
    
        std::vector<SerialMessage> serialMessages;
    
        LedLine ledLine[NUM_LEDLINES];
    
        int current_msg_string;
        string msg_strings[NUM_MSG_STRINGS];
        float timers[NUM_MSG_STRINGS];

    
    
};
