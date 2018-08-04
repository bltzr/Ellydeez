#pragma once

#include <stdio.h>

#include "ofMain.h"

#include "sinks/SinkFactory.hpp"
#include "sources/SourceFactory.hpp"

using namespace std;

class ofApp : public ofBaseApp {

public:
    
    void setup();
    void update();
    void draw();
    void exit();
    
private:
    
    void config(ofJson jsConfig);
    
    ofJson          conf;
    
    string          name {"Ellydeez"};
    int             fps{60};
    
    SourceFactory   sources;
    SinkFactory     sinks;
    
    bool            running {true};
    bool            drawing {true};
    

};
