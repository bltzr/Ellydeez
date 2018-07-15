#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){

    // Try to load JSON config file
    ofFile file("config.json");
    if(file.exists()){
        file >> js;
        for(auto & field : js){
            if(!field.empty()){
                for(auto & src: field){
                    std::cout<<src;
                }
            }
        }
    }
    
    // display
    ofSetWindowTitle(windowName);
    ofSetVerticalSync(false);
    ofSetFrameRate(fps);
    
    
    // Serial
    
    ofLog() << "List of connected serial devices:";
    Sinks::printSerialDevices(); // display the list of devices in the Log Window
    ofLog() << "Opening serial devices:";

    device[0].name = portName(3262750); //"/dev/cu.usbmodem3767281"; //
    
    
    /*
    device[0].name = "/dev/cu.usbmodem1369841";
    device[1].name = "/dev/cu.usbmodem1455771";
    device[2].name = "/dev/cu.usbmodem1383111";
    
    for (int i = 0; i< NUM_TEENSIES; ++i){
        device[i].setup();
    }
     */

    
    // LED lines assignments
    
    // Verticaux:
    
    ledLine[0].dev = &device[0];
    ledLine[0].source = &pixels;
    ledLine[0].address = "/1";
    ledLine[0].nbPix = 128;
    ledLine[0].Yoffset = 0;
    ledLine[0].Ysize = 1;
    ledLine[0].Xsize = 128;
    
    ledLine[1].dev = &device[0];
    ledLine[1].source = &pixels;
    ledLine[1].address = "/2";
    ledLine[1].nbPix = 132;
    ledLine[1].Yoffset = 1;
    ledLine[1].Ysize = 1;
    ledLine[1].Xsize = 132;
    
    
    // Calculate our drawing size
    
    if (drawXsize == 0 && drawYsize == 0){
        for (int i = 0; i < NUM_LEDLINES; ++i){
            if(drawXsize<ledLine[i].Xsize) drawXsize=ledLine[i].Xsize;
            drawYsize+=ledLine[i].Ysize;
        }
        for (int i = 0; i < NUM_DMXLINES; ++i){
            if(drawXsize<ledLine[i].Xsize) drawXsize=ledLine[i].Xsize;
            drawYsize+=ledLine[i].Ysize;
        }
    }
    
    //Initial FBO allocation and cleanup
    
    cout << "sizes: " << drawXsize << " / " << drawYsize << endl;
    fbo.allocate(drawXsize, drawYsize, GL_RGB);
    fbo.begin();
    ofDisableAlphaBlending();
    ofClear(0,0,0,0);
    fbo.end();
}


//--------------------------------------------------------------
void ofApp::update(){

    // Time management
    
    ++timeCounter;
    if (timeCounter>100){
        Poco::Timestamp now;
        Poco::LocalDateTime nowLocal(now);
        std::string fmt = Poco::DateTimeFormat::SORTABLE_FORMAT;
        std::string timeNow = ofxTime::Utils::format(ofxTime::Utils::floor(nowLocal, Poco::Timespan::MINUTES), fmt);
        currentTime = (int(timeNow[11])-48)*10+int(timeNow[12])-48;
        bool previousTime = timeToPlay;
        timeToPlay = (currentTime > 10 && currentTime < 19);
        //if(timeToPlay!=previousTime){playing=timeToPlay; cout << "play: " << playing << endl; }
        timeCounter=0;
    }
    
    
    // Treat incoming OSC Messages:
    
    while(receiver.hasWaitingMessages()){
        // get the next message
        ofxOscMessage m;
        receiver.getNextMessage(m);
        /*
        if(m.getAddress() == "/b"){
            ofLog() << "b" << m.getArgAsInt32(0);
            for (int i=0; i<NUM_LEDLINES; i++){
                ledLine[i].setBrightness(m.getArgAsInt32(0));
            }
        }
        else if(m.getAddress() == "/d"){
            for (int i=0; i<NUM_LEDLINES; i++){
                ledLine[i].setDither(m.getArgAsInt32(0));
            }
            ofLog() << "d" << m.getArgAsInt32(0);
        }
        else */if(m.getAddress() == "/play"){
            ofLog() << "play" << m.getArgAsInt32(0);
            if(m.getArgAsBool(0)){trame.play(); trame.setLoopState(OF_LOOP_NORMAL); playing = 1;}
            else if(!m.getArgAsBool(0)){trame.stop(); playing = 0;}
        }
        else if(m.getAddress() == "/pause"){
            ofLog() << "pause" << m.getArgAsInt32(0);
            if(m.getArgAsBool(0)){trame.setPaused(1);}
            
            else if(!m.getArgAsBool(0)){trame.setPaused(0);}
        }
        else if(m.getAddress() == "/draw"){
            ofLog() << "draw" << m.getArgAsInt32(0);
            drawing = m.getArgAsBool(0);
        }
        else if(m.getAddress() == "/position"){
            ofLog() << "position" << m.getArgAsFloat(0);
            trame.setPosition(m.getArgAsFloat(0));
        }
        else if(m.getAddress() == "/speed"){
            ofLog() << "speed" << m.getArgAsFloat(0);
            trame.setSpeed(m.getArgAsFloat(0));
        }
    }
    
    
    // Get Data from the sources:
    
    if(playing){                        // Data from a movie
        
        trame.update();
        pixels = trame.getPixels();
        
    } else {                            // Data from Syphon
        
        // If the source dimensions change, we reallocate the FBO to the right sizes
        if ((mClient.getTexture().getWidth()!=0&&mClient.getTexture().getHeight()!=0)
         &&(sourceXsize!=mClient.getTexture().getWidth() ||
            sourceYsize!=mClient.getTexture().getHeight())){
            
            cout << "Syphon Input: width/height: " << mClient.getTexture().getWidth() << " " << mClient.getTexture().getHeight() << endl;
            sourceXsize=mClient.getTexture().getWidth();
            sourceYsize=mClient.getTexture().getHeight();
            fbo.allocate(sourceXsize, sourceYsize, GL_RGB);
            fbo.begin();
            ofDisableAlphaBlending();
            ofClear(0,0,0);
            fbo.end();
        }
        
        
        // FBO operations:
        
        fbo.begin();
        ofDisableAlphaBlending();
        mClient.draw(0, 0, drawXsize, drawYsize);
        fbo.end();
        
        fbo.readToPixels(pixels);
    
    }
    
    // Temporary hack to get the brightnesses from the video
    /// TODO: turn this into (a) proper class(es)
    
    pixels.cropTo(BrightPix, 129, 0, 3, 1);
    Brights = BrightPix.getData();
    
    for (int i=0; i<NUM_LEDLINES; i++){
        ledLine[i].setDither(int(Brights[0]));
    }
    //cout << "D" << int(Brights[1]) << endl;
    
    for (int i=0; i<NUM_LEDLINES; i++){
        ledLine[i].setBrightness(int(Brights[(i+1)*3]));
        // cout << "B " << i << ": " << int(Brights[(i+1)*3]) << endl;
    }
    
    
    // Send the whole thing to the LED/DMX lines:
    
    for (int i=0; i<NUM_LEDLINES; i++) {
        ledLine[i].sendLine();
    }
    for (int i=0; i<NUM_DMXLINES; i++) {
        dmxLine[i].sendLine();
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
    
    }
    
    #endif

}





