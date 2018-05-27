#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){

    // display
    ofSetWindowTitle("Ellydeez");
    ofSetFrameRate(60); // if vertical sync is off, we can go a bit fast... this caps the framerate at 60fps.
    
    // OSC
    receiver.setup(PORTIN);
    ofLog() << "Opened OSC Receiver";
    
    // Syphon
    mClient.setup();
    mClient.set("","Simple Server"); // Use Syphon Simple Server to test this, change arguments at will

    // Video Player
    trame.setPixelFormat(OF_PIXELS_RGB);
    trame.load("test.mov");
    trame.setLoopState(OF_LOOP_NORMAL);
    
    if(playing){
        trame.play();
        trame.setSpeed(1);
    }

    
    // Serial
    bool printDevices = true;        // Set this to true to display the list of devices in the Log Window
    int devNumb = 0;
    if (printDevices){
        std::vector<ofx::IO::SerialDeviceInfo> devicesInfo = ofx::IO::SerialDeviceUtils::listDevices();
        ofLogNotice("ofApp::setup") << "Connected Devices: ";
        for (ofx::IO::SerialDeviceInfo d : devicesInfo){
            ofLogNotice("  ") << devNumb << ": " << d;
            ++devNumb;
        }
    }
    
    ofLog() << "Opening serial devices:";
    
    device[0].name = "/dev/cu.usbmodem1369841";
    device[1].name = "/dev/cu.usbmodem1455771";
    device[2].name = "/dev/cu.usbmodem1383111";
    
    for (int i = 0; i< NUM_TEENSIES; ++i){
        device[i].setup();
    }

    
    // LED lines assignments
    
    ledLine[0].dev = &device[0];
    ledLine[0].src = &pixels;
    ledLine[0].address = "/1";
    ledLine[0].nbPix = 264;
    ledLine[0].Yoffset = 0;
    ledLine[0].Ysize = 4;
    ledLine[0].Xsize = 66;
    
    ledLine[1].dev = &device[0];
    ledLine[1].src = &pixels;
    ledLine[1].address = "/2";
    ledLine[1].nbPix = 264;
    ledLine[1].Yoffset = 4;
    ledLine[1].Ysize = 4;
    ledLine[1].Xsize = 66;

    ledLine[2].dev = &device[1];
    ledLine[2].src = &pixels;
    ledLine[2].address = "/1";
    ledLine[2].nbPix = 81;
    ledLine[2].Yoffset = 8;
    ledLine[2].Ysize = 4;
    ledLine[2].Xsize = 66;

    ledLine[3].dev = &device[1];
    ledLine[3].src = &pixels;
    ledLine[3].address = "/2";
    ledLine[3].nbPix = 264;
    ledLine[3].Yoffset = 12;
    ledLine[3].Ysize = 4 ;
    ledLine[3].Xsize = 66;
    
    ledLine[4].dev = &device[2];
    ledLine[4].src = &pixels;
    ledLine[4].address = "/1";
    ledLine[4].nbPix = 264;
    ledLine[4].Yoffset = 16;
    ledLine[4].Ysize = 4;
    ledLine[4].Xsize = 66;
    
    dmxLine[0].dev = &device[2];
    dmxLine[0].src = &pixels;
    dmxLine[0].address = "/DMX";
    dmxLine[0].nbPix = 12;
    dmxLine[0].Yoffset = 20;
    dmxLine[0].Ysize = 1;
    dmxLine[0].Xsize = 1;
    
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
    ofDisableAlphaBlending();
    fbo.begin();
    ofClear(0,0,0);
    fbo.end();
}


//--------------------------------------------------------------
void ofApp::update(){

    // Treat incoming OSC Messages:
    
    while(receiver.hasWaitingMessages()){
        // get the next message
        ofxOscMessage m;
        receiver.getNextMessage(m);
        
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
        else if(m.getAddress() == "/play"){
            ofLog() << "play" << m.getArgAsInt32(0);
            if(m.getArgAsBool(0)){trame.play(); playing = 1;}
            else if(!m.getArgAsBool(0)){trame.stop(); playing = 0;}
        }
        else if(m.getAddress() == "/pause"){
            ofLog() << "pause" << m.getArgAsInt32(0);
            if(m.getArgAsBool(0)){trame.setPaused(1);}
            
            else if(!m.getArgAsBool(0)){trame.setPaused(1);}
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
    
    pixels.cropTo(BrightPix, 0, 12, 2, 1);
    Brights = BrightPix.getData();
    
    for (int i=0; i<NUM_LEDLINES; i++){
        ledLine[i].setDither(int(Brights[0]));
    }
    //cout << "d: " << int(Brights[0]) << endl;
    
    for (int i=0; i<6; i++){
        ledLine[i].setBrightness(int(Brights[3]/8));
    }
    //cout << "b: " << int(int(Brights[3]/8)) << endl;
  
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
        img.draw(500, ledLine[i].Yoffset*15+20, 450, ledLine[i].Ysize*10);
    }
    
    // DMX display
    for (int i=0; i<NUM_DMXLINES; i++) {
        ofImage img;
        img.setFromPixels(dmxLine[i].pixelCrop);
        img.draw(500, dmxLine[i].Yoffset*15+50, 450, dmxLine[i].Ysize*50);
    }
    
    // dither + brightness display
    ofImage img;
    img.setFromPixels(BrightPix);
    img.draw(500, dmxLine[NUM_DMXLINES-1].Yoffset*15+80+ledLine[NUM_LEDLINES-1].Ysize*10, 450, 50);
    
    
    #endif

}
//------------------------------------------------------------------------



    /// TODO: check that we really need this:

//------------------------------------------------------------------------
// Serial messages management
//
void ofApp::onSerialBuffer(const ofx::IO::SerialBufferEventArgs& args)
{
    // Decoded serial packets will show up here.
    SerialMessage message(args.getBuffer().toString(), "", 255);
    serialMessages.push_back(message);
    
    // ofLogNotice("onSerialBuffer") << "got serial buffer : " << message.message;
}


void ofApp::onSerialError(const ofx::IO::SerialBufferErrorEventArgs& args)
{
    // Errors and their corresponding buffer (if any) will show up here.
    SerialMessage message(args.getBuffer().toString(),
                          args.getException().displayText(),
                          500);
    
    serialMessages.push_back(message);
    ofLogNotice("onSerialError") << "got serial error : " << message.exception;
}


