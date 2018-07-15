#pragma once

#include <stdio.h>

#include "ofMain.h"

#include "SinkPool.hpp"
#include "SourcePool.hpp"


//--------------------------------------------------------------
//    Our App

class ofApp : public ofBaseApp {

public:
    void setup();
    void update();
    void draw();
    void exit();
    
    ofJson js;
    
    std::string windowName {"Ellydeez"};
    int         fps{60};
    
    SourcePool  sources;
    SinkPool    sinks;
    
    int playing = 1;
    
    
    // v move this in the appropriate classes


    int sourceXsize = 0, sourceYsize = 0;
    int drawXsize = 132, drawYsize = 2;

    
    // temporary way to deal with brightness info from the video:
    ofPixels BrightPix;
    unsigned char * Brights;

    


};
