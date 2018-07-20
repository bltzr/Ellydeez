#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
    
    // Serial
    
    ofLog() << "List of connected serial devices:";
    Sinks::Devices::printSerialDevices(); // display the list of devices in the Log Window
    

    // Try to load JSON config file
    ofFile file("config.json");
    if(file.exists()){
        file >> conf;
        
        config( conf["config"] );
        sources.setup( conf["sources"] );
        sinks.setup( conf["sinks"] );
        sources.addPools( conf[ "pools" ] );
        
    }
    
    // display
    ofSetWindowTitle(name);
    ofSetVerticalSync(false);
    ofSetFrameRate(fps);
    
}


//--------------------------------------------------------------
void ofApp::update(){

    if (running){

        sources.update();
        sinks.update();
        
    }
}


//-------------------------------------------------------------------------
// Draw the current state of operations (Desktop only, this won't happen on Pi)
//
void ofApp::draw(){
  
    #ifdef __APPLE__
  
    if (drawing){
        
    // Clear with alpha, so we can capture via syphon and composite elsewhere should we want.
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /*
    if(playing){
        
        trame.draw(20, 20, 450, 450);
        
    } else {
    
        fbo.draw(20, 20, 450, 450);
        
    }
  
    
    // LED lines display
    for (int i=0; i<NUM_LEDLINES; i++) {
        ofImage img;
        img.setFromPixels(ledLine[i].pixelCrop);
        img.draw(500, ledLine[i].Yoffset*10+20, 450, ledLine[i].Ysize*8);
    }
    
    // DMX display
    for (int i=0; i<NUM_DMXLINES; i++) {
        ofImage img;
        img.setFromPixels(dmxLine[i].pixelCrop);
        img.draw(500, dmxLine[i].Yoffset*10+50, 450, dmxLine[i].Ysize*8);
    }
    
    // dither + brightness display
    ofImage img;
    img.setFromPixels(BrightPix);
    img.draw(500, dmxLine[NUM_DMXLINES-1].Yoffset*10+80+ledLine[NUM_LEDLINES-1].Ysize*18, 450, 50);
     
     */
    
    }
    
    #endif

}

void ofApp::exit(){
}

void ofApp::config( ofJson c ) {

    for(auto src = c.begin(); src!= c.end(); ++src ){
        if      (src.key() == "name") name = src.value();
        else if (src.key() == "fps")  fps = src.value();
        else ofLogError("config")
            << "extra field for config: " << src.key()
            << " with value: " << src.value() << endl;
    }
    
}


