#pragma once

#include "ofMain.h"
#include "ofxTime.h"

#include "SinkPool.hpp"
#include "SourcePool.hpp"


// project-specific numbers:
#define PORTIN 66666            // for incoming OSC messages



//--------------------------------------------------------------
//    Our App

class ofApp : public ofBaseApp {

public:
    void setup();
    void update();
    void draw();
    void exit();
    
    ofJson js;
    ofPath path;
    
    std::string windowName {"Ellydeez"};
    int         fps{60};
    
    SourcePool  sources;
    SinkPool    sinks;
    
    int playing = 1;
    
    
    
    // v move this in the appropriate classes
    
    ofxOscReceiver receiver;

    int sourceXsize = 0, sourceYsize = 0;
    int drawXsize = 132, drawYsize = 2;

    
    // temporary way to deal with brightness info from the video:
    ofPixels BrightPix;
    unsigned char * Brights;

    


};
