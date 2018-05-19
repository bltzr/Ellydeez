#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){

    // display
    ofSetWindowTitle("ledMapper");
    ofSetFrameRate(60); // if vertical sync is off, we can go a bit fast... this caps the framerate at 60fps.
    
    // OSC
    receiver.setup(PORTIN);
    ofLog() << "Opened OSC Receiver";
   
    // Syphon
    mClient.setup();
    mClient.set("","Simple Server"); // Use Syphon Simple Server to test this, change arguments at will

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
    ledLine[3].Ysize = 2;
    ledLine[3].Xsize = 66;
    
    ledLine[4].dev = &device[2];
    ledLine[4].src = &pixels;
    ledLine[4].address = "/1";
    ledLine[4].nbPix = 264;
    ledLine[4].Yoffset = 16;
    ledLine[4].Ysize = 4;
    ledLine[4].Xsize = 66;
    
    ledLine[5].dev = &device[2];
    ledLine[5].src = &pixels;
    ledLine[5].address = "/2";
    ledLine[5].nbPix = 264;
    ledLine[5].Yoffset = 20;
    ledLine[5].Ysize = 4;
    ledLine[5].Xsize = 66;
    
     
    // Calculate our drawing size
    
    for (int i = 0; i < NUM_LEDLINES; ++i){
        if(drawXsize<ledLine[i].Xsize) drawXsize=ledLine[i].Xsize;
        drawYsize+=ledLine[i].Ysize;
    }
    
    //Initial FBO allocation and cleanup
    
    fbo.allocate(drawXsize, drawYsize, GL_RGB);
    fbo.begin();
    ofClear(0,0,0);
    fbo.end();
}

//--------------------------------------------------------------
void ofApp::update(){

    
    // If the source dimensions change, we reallocate the FBO to the right sizes
    
    if (sourceXsize!=mClient.getTexture().getWidth() || sourceYsize!=mClient.getTexture().getHeight()){
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
    mClient.draw(0, 0, drawXsize, drawYsize);
    fbo.end();
    
    fbo.readToPixels(pixels);
    
    
    // Treat incoming OSC Messages:
    
    while(receiver.hasWaitingMessages()){
        // get the next message
        ofxOscMessage m;
        receiver.getNextMessage(m);
        
        if(m.getAddress() == "/b"){
            ofLog() << "b" << m.getArgAsInt32(0);
            for (int i=0; i<6; i++){
                ledLine[i].setBrightness(m.getArgAsInt32(0));
            }
        }
        else if(m.getAddress() == "/d"){
            for (int i=0; i<6; i++){
                ledLine[i].setDither(m.getArgAsInt32(0));
            }
            ofLog() << "d" << m.getArgAsInt32(0);
        }
    }
  
    // Send the whole thing to the LED lines:
    
    for (int i=0; i<6; i++) {
    ledLine[i].sendLine();
    }
    
}

//------------------------------------------------------------------------
// Draw the current state of operations (Mac only, this won't happen on Pi
//
void ofApp::draw(){
  
    #ifdef __APPLE__
  
    // Clear with alpha, so we can capture via syphon and composite elsewhere should we want.
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    
    fbo.draw(20, 20, 450, 450);
    
    for (int i=0; i<6; i++) {
        ofImage img;
        img.setFromPixels(ledLine[i].pixelCrop);
        img.draw(500, ledLine[i].Yoffset*15+20, 450, ledLine[i].Ysize*10);
    }
    
    #endif

}
//------------------------------------------------------------------------





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


