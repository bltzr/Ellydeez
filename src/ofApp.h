#pragma once

#include <stdio.h>

#include "ofMain.h"

#include "SinkFactory.hpp"
#include "SourceFactory.hpp"

using namespace std;

class ofApp : public ofBaseApp {

public:
    
    void setup();
    void update();
    void draw();
    void exit();
    
    
    ofJson          js;
    
    string          name {"Ellydeez"};
    int             fps{60};
    
    SourceFactory   sources;
    SinkFactory     sinks;
    
    bool            running {true};
    bool            drawing {true};
    

};
