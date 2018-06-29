#include "ofApp.h"



//--------------------------------------------------------------
void ofApp::setup(){

    // display
    ofSetWindowTitle("AdAstra");
    ofSetFrameRate(60); // if vertical sync is off, we can go a bit fast... this caps the framerate at 60fps.
    ofSetVerticalSync(false);
    
    // OSC
    receiver.setup(PORTIN);
    ofLog() << "Opened OSC Receiver";
    
    // Syphon
    mClient.setup();
    mClient.set("AdAstra","Max"); // Use Syphon Simple Server to test this, change arguments at will

    // Video Player
    trame.setPixelFormat(OF_PIXELS_RGB);
    trame.load("test.mov");
    
    if(playing){
        trame.play();
        trame.setSpeed(1);
        trame.setLoopState(OF_LOOP_NORMAL);
    }

    
    // Serial
    bool printDevices = true;        // Set this to true to display the list of devices in the Log Window
    int devNumb = 0;
    //if (printDevices){
    devicesInfo = ofx::IO::SerialDeviceUtils::listDevices();
    
    ofLogNotice("ofApp::setup") << "Connected Devices: ";
    for (ofx::IO::SerialDeviceInfo d : devicesInfo){
        ofLogNotice("  ") << devNumb << ": " << d;
        ++devNumb;
    }
    //}
    
    ofLog() << "Opening serial devices:";
    
    // Verticaux
    device[0].name = portName(3767280); //"/dev/cu.usbmodem3767281";
    device[1].name = portName(1382270); //"/dev/cu.usbmodem1382271";
    device[2].name = portName(4115750); //"/dev/cu.usbmodem4115751";
    //Plafond
    device[3].name = portName(4115530); //"/dev/cu.usbmodem4115531";
    device[4].name = portName(4115540); //"/dev/cu.usbmodem4115541";
    device[5].name = portName(3960030); //"/dev/cu.usbmodem3960031";
    device[6].name = portName(3962840); //"/dev/cu.usbmodem3962841";
    device[7].name = portName(3884290); //"/dev/cu.usbmodem3884291";
    device[8].name = portName(4115520); //"/dev/cu.usbmodem4115521"; // + DMX
    
    
    
    for (int i = 0; i< NUM_TEENSIES; ++i){
        device[i].setup();
    }

    
    // LED lines assignments
    
    // Verticaux:
    
    ledLine[0].dev = &device[0];
    ledLine[0].src = &pixels;
    ledLine[0].address = "/1";
    ledLine[0].nbPix = 134;
    ledLine[0].Yoffset = 0;
    ledLine[0].Ysize = 1;
    ledLine[0].Xsize = 134;
    
    ledLine[1].dev = &device[0];
    ledLine[1].src = &pixels;
    ledLine[1].address = "/2";
    ledLine[1].nbPix = 134;
    ledLine[1].Yoffset = 1;
    ledLine[1].Ysize = 1;
    ledLine[1].Xsize = 134;
    
    ledLine[2].dev = &device[1];
    ledLine[2].src = &pixels;
    ledLine[2].address = "/1";
    ledLine[2].nbPix = 134;
    ledLine[2].Yoffset = 2;
    ledLine[2].Ysize = 1;
    ledLine[2].Xsize = 134;
    
    ledLine[3].dev = &device[1];
    ledLine[3].src = &pixels;
    ledLine[3].address = "/2";
    ledLine[3].nbPix = 134;
    ledLine[3].Yoffset = 3;
    ledLine[3].Ysize = 1 ;
    ledLine[3].Xsize = 134;
    
    ledLine[4].dev = &device[2];
    ledLine[4].src = &pixels;
    ledLine[4].address = "/1";
    ledLine[4].nbPix = 134;
    ledLine[4].Yoffset = 4;
    ledLine[4].Ysize = 1;
    ledLine[4].Xsize = 134;
    
    ledLine[5].dev = &device[2];
    ledLine[5].src = &pixels;
    ledLine[5].address = "/2";
    ledLine[5].nbPix = 134;
    ledLine[5].Yoffset = 5;
    ledLine[5].Ysize = 1;
    ledLine[5].Xsize = 134;
    
    
    // Plafond:
    
    ledLine[6].dev = &device[3];
    ledLine[6].src = &pixels;
    ledLine[6].address = "/1";
    ledLine[6].nbPix = 92;
    ledLine[6].Yoffset = 6;
    ledLine[6].Ysize = 1;
    ledLine[6].Xsize = 92;
    
    ledLine[7].dev = &device[3];
    ledLine[7].src = &pixels;
    ledLine[7].address = "/2";
    ledLine[7].nbPix = 92;
    ledLine[7].Yoffset = 7;
    ledLine[7].Ysize = 1;
    ledLine[7].Xsize = 92;
    
    ledLine[8].dev = &device[4];
    ledLine[8].src = &pixels;
    ledLine[8].address = "/1";
    ledLine[8].nbPix = 92;
    ledLine[8].Yoffset = 8;
    ledLine[8].Ysize = 1;
    ledLine[8].Xsize = 92;
    
    ledLine[9].dev = &device[4];
    ledLine[9].src = &pixels;
    ledLine[9].address = "/2";
    ledLine[9].nbPix = 92;
    ledLine[9].Yoffset = 9;
    ledLine[9].Ysize = 1;
    ledLine[9].Xsize = 92;
    
    ledLine[10].dev = &device[5];
    ledLine[10].src = &pixels;
    ledLine[10].address = "/1";
    ledLine[10].nbPix = 92;
    ledLine[10].Yoffset = 10;
    ledLine[10].Ysize = 1;
    ledLine[10].Xsize = 92;
    
    ledLine[11].dev = &device[5];
    ledLine[11].src = &pixels;
    ledLine[11].address = "/2";
    ledLine[11].nbPix = 92;
    ledLine[11].Yoffset = 11;
    ledLine[11].Ysize = 1;
    ledLine[11].Xsize = 92;
    
    ledLine[12].dev = &device[6];
    ledLine[12].src = &pixels;
    ledLine[12].address = "/1";
    ledLine[12].nbPix = 92;
    ledLine[12].Yoffset = 12;
    ledLine[12].Ysize = 1;
    ledLine[12].Xsize = 92;
    
    ledLine[13].dev = &device[6];
    ledLine[13].src = &pixels;
    ledLine[13].address = "/2";
    ledLine[13].nbPix = 92;
    ledLine[13].Yoffset = 13;
    ledLine[13].Ysize = 1;
    ledLine[13].Xsize = 92;
    
    ledLine[14].dev = &device[7];
    ledLine[14].src = &pixels;
    ledLine[14].address = "/1";
    ledLine[14].nbPix = 92;
    ledLine[14].Yoffset = 14;
    ledLine[14].Ysize = 1;
    ledLine[14].Xsize = 92;
    
    ledLine[15].dev = &device[7];
    ledLine[15].src = &pixels;
    ledLine[15].address = "/2";
    ledLine[15].nbPix = 92;
    ledLine[15].Yoffset = 15;
    ledLine[15].Ysize = 1;
    ledLine[15].Xsize = 92;
    
    ledLine[16].dev = &device[8];
    ledLine[16].src = &pixels;
    ledLine[16].address = "/1";
    ledLine[16].nbPix = 92;
    ledLine[16].Yoffset = 16;
    ledLine[16].Ysize = 1;
    ledLine[16].Xsize = 92;
    
    ledLine[17].dev = &device[8];
    ledLine[17].src = &pixels;
    ledLine[17].address = "/2";
    ledLine[17].nbPix = 92;
    ledLine[17].Yoffset = 17;
    ledLine[17].Ysize = 1;
    ledLine[17].Xsize = 92;
    
    dmxLine[0].dev = &device[8];
    dmxLine[0].src = &pixels;
    dmxLine[0].address = "/DMX";
    dmxLine[0].nbPix = 12;
    dmxLine[0].Yoffset = 18;
    dmxLine[0].Ysize = 1;
    dmxLine[0].Xsize = 3;
    
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
    
    pixels.cropTo(BrightPix, 130, 18, 2, 1);
    Brights = BrightPix.getData();
    
    for (int i=0; i<NUM_LEDLINES; i++){
        ledLine[i].setDither(int(Brights[0]));
    }
    //cout << "D" << int(Brights[1]) << endl;
    
    for (int i=0; i<NUM_LEDLINES; i++){
        ledLine[i].setBrightness(int(Brights[3]/8));
    }
    //cout << "B" << int(Brights[4]) << endl;
    
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


