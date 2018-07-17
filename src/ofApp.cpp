#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){

    // Try to load JSON config file
    ofFile file("config.json");
    if(file.exists()){
        file >> js;
        for(auto field = js.begin(); field != js.end(); ++field ){
            //if(!field.empty()){
            cout << "name: " << field.key() << endl;
            auto& fw = field.value();
            for(auto src = fw.begin(); src!= fw.end(); ++src ){
                cout << "name: " << src.key() << endl;
                cout << "content: " << endl << setw(4) << src.value() << endl;
               // }
            }
        }
    }
    
    // Sources and Sinks
    
    sources.setup();
    sinks.setup();
    
    // display
    ofSetWindowTitle(name);
    ofSetVerticalSync(false);
    ofSetFrameRate(fps);
    
    
    // Serial
    
    ofLog() << "List of connected serial devices:";
    Sinks::printSerialDevices(); // display the list of devices in the Log Window
    ofLog() << "Opening serial devices:";

   
    
    
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



