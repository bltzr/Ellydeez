#pragma once

#include "ofMain.h"
#include "ofxSyphon.h"
#include "ofxSerial.h"
#include "ofxOsc.h"
#include "ofxIO.h"

#define NUM_MSG_STRINGS 20




// project-specific numbers:
#define NUM_TEENSIES 3          // How many Teensies to use ?
#define NUM_LEDLINES 6          // How many physical LED lines ?
#define NUM_SYPHON 1            // How many Syphon clients ?
#define PORTIN 66666              // for incoming OSC messages




//--------------------------------------------------------------
//      Our utility classes /// TODO: move to another file
//--------------------------------------------------------------
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

//--------------------------------------------------------------
class LedLine
{
public:
    ofPixels * src;  // source
    string address;  // OSC address
    int nbPix;       // number of pixels
    int Xoffset;
    int Yoffset;     // how many lines to offset from
    int Xsize;       // X length of the line
    int Ysize;       // how many lines to include
    OSC2APA102 * dev;
    ofPixels pixelCrop;
    uint8_t brightness;
    uint8_t dither;
    
};
//--------------------------------------------------------------



//--------------------------------------------------------------
//      Our App's variables and methods:
//--------------------------------------------------------------
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
        void sendLine(int i);
        void setBrightness(int line, int brightness);
        void setDither(int line, int dither);
  
        OSC2APA102 device[NUM_TEENSIES] ;
    
        std::vector<SerialMessage> serialMessages;
    
        LedLine ledLine[NUM_LEDLINES];
    
        int current_msg_string;
        string msg_strings[NUM_MSG_STRINGS];
        float timers[NUM_MSG_STRINGS];
    
    
    private:
        void appendMessage( ofxOscMessage& message, osc::OutboundPacketStream& p );
    
};
