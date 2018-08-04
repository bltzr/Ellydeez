#pragma once

#include <stdio.h>

#include "ofMain.h"
#include "ofxOscQueryServer.h"
#include "SinkFactory.hpp"
#include "SourceFactory.hpp"

using namespace std;

class ofApp : public ofBaseApp {

public:
    
    void setup();
    void update();
    void draw();
    void exit();
    
    void fpsChanged();
    
private:
    
    void config(ofJson jsConfig);
    
    ofJson              conf;
    
    string              name {"Ellydeez"};
    
    int                 OSCport {4321};
    int                 WSPort  {8765};
    //ofxOscQueryServer   server{OSCport, WSPort};
    
    ofParameterGroup    parameters;
    
    
    ofParameter<int>    fps{60};
    
    SourceFactory       sources;
    SinkFactory         sinks;
    
    bool                running {true};
    bool                drawing {true};
    

};
