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
                setBrightness(i, m.getArgAsInt32(0));
            }
        }
        else if(m.getAddress() == "/d"){
            for (int i=0; i<6; i++){
                setDither(i, m.getArgAsInt32(0));
            }
            ofLog() << "d" << m.getArgAsInt32(0);
        }
    }
  
    // Send the whole thing to the LED lines:
    
    for (int i=0; i<6; i++) {
    sendLine(i);
    }
    
}

//--------------------------------------------------------------
// Set APA102 Brightness for each LED line:
//
void ofApp::setBrightness(int i, int brightness) {

    // check for waiting messages
    
        LedLine line = ledLine[i];
        ofxOscMessage n;
        n.setAddress(line.address);
        n.addIntArg(brightness);
        
        // this code come from ofxOscSender::sendMessage in ofxOscSender.cpp
        static const int OUTPUT_BUFFER_SIZE = 16384;
        char buffer[OUTPUT_BUFFER_SIZE];
        osc::OutboundPacketStream p( buffer, OUTPUT_BUFFER_SIZE );
        
        // serialise the message
        
        p << osc::BeginBundleImmediate;
        appendMessage( n, p );
        p << osc::EndBundle;
        
        ofx::IO::ByteBuffer toEncode(p.Data(),p.Size());
        
        try {
            line.dev->dev.send(toEncode);
        } catch ( serial::SerialException e) {
            ofLogError("sendLine") << "failed to send data : " << e.what();
            line.dev->setup();
        }

}

//--------------------------------------------------------------
// Set FastLED Brightness (aka dither) for each LED line:
//
void ofApp::setDither(int i, int dither) {
  
        // check for waiting messages
        
        LedLine line = ledLine[i];
        ofxOscMessage n;
        n.setAddress("/b");
        n.addIntArg(dither);
        
        // this code come from ofxOscSender::sendMessage in ofxOscSender.cpp
        static const int OUTPUT_BUFFER_SIZE = 16384;
        char buffer[OUTPUT_BUFFER_SIZE];
        osc::OutboundPacketStream p( buffer, OUTPUT_BUFFER_SIZE );
        
        // serialise the message
        
        p << osc::BeginBundleImmediate;
        appendMessage( n, p );
        p << osc::EndBundle;
        
        ofx::IO::ByteBuffer toEncode(p.Data(),p.Size());
        
        try {
          line.dev->dev.send(toEncode);
        } catch ( serial::SerialException e) {
          ofLogError("sendLine") << "failed to send data : " << e.what();
          line.dev->setup();
        }
  
}

//--------------------------------------------------------------
// Send the whole thing to each LED line:
//
void ofApp::sendLine(int i) {

    LedLine &line = ledLine[i];
    //ofPixels pixelCrop;
    line.src->cropTo(line.pixelCrop, 0 , line.Yoffset, line.Xsize, line.Ysize);
    
    ofBuffer imgAsBuffer;
    imgAsBuffer.clear();
    imgAsBuffer.append((const char*)line.pixelCrop.getData(),line.nbPix*3);
    
    ofxOscMessage m;
    m.setAddress(line.address);
    m.addBlobArg(imgAsBuffer);
    
    // this code comes from ofxOscSender::sendMessage in ofxOscSender.cpp
    static const int OUTPUT_BUFFER_SIZE = 16384;
    char buffer[OUTPUT_BUFFER_SIZE];
    osc::OutboundPacketStream p( buffer, OUTPUT_BUFFER_SIZE );
    
    // serialise the message
    p << osc::BeginBundleImmediate;
    appendMessage( m, p );
    p << osc::EndBundle;
    
    ofx::IO::ByteBuffer toEncode(p.Data(),p.Size());
    
    try {
        line.dev->dev.send(toEncode);
    } catch ( serial::SerialException e) {
        ofLogError("sendLine") << "failed to send data : " << e.what();
        line.dev->setup();
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

void ofApp::appendMessage( ofxOscMessage& message, osc::OutboundPacketStream& p )
{
    p << osc::BeginMessage( message.getAddress().c_str() );
	for ( int i=0; i< message.getNumArgs(); ++i )
	{
		if ( message.getArgType(i) == OFXOSC_TYPE_INT32 )
			p << message.getArgAsInt32( i );
		else if ( message.getArgType(i) == OFXOSC_TYPE_INT64 )
			p << (osc::int64)message.getArgAsInt64( i );
		else if ( message.getArgType( i ) == OFXOSC_TYPE_FLOAT )
			p << message.getArgAsFloat( i );
		else if ( message.getArgType( i ) == OFXOSC_TYPE_DOUBLE )
			p << message.getArgAsDouble( i );
		else if ( message.getArgType( i ) == OFXOSC_TYPE_STRING || message.getArgType( i ) == OFXOSC_TYPE_SYMBOL)
			p << message.getArgAsString( i ).c_str();
		else if ( message.getArgType( i ) == OFXOSC_TYPE_CHAR )
			p << message.getArgAsChar( i );
		else if ( message.getArgType( i ) == OFXOSC_TYPE_MIDI_MESSAGE )
			p << message.getArgAsMidiMessage( i );
		else if ( message.getArgType( i ) == OFXOSC_TYPE_TRUE || message.getArgType( i ) == OFXOSC_TYPE_FALSE )
			p << message.getArgAsBool( i );
		else if ( message.getArgType( i ) == OFXOSC_TYPE_TRIGGER )
			p << message.getArgAsTrigger( i );
		else if ( message.getArgType( i ) == OFXOSC_TYPE_TIMETAG )
			p << (osc::int64)message.getArgAsTimetag( i );
		//else if ( message.getArgType( i ) == OFXOSC_TYPE_RGBA_COLOR )
		//	p << message.getArgAsRgbaColor( i );
        else if ( message.getArgType( i ) == OFXOSC_TYPE_BLOB ){
            ofBuffer buff = message.getArgAsBlob(i);
            osc::Blob b(buff.getData(), (unsigned long)buff.size());
            p << b; 
		}else
		{
			ofLogError("ofxOscSender") << "appendMessage(): bad argument type " << message.getArgType( i );
			assert( false );
		}
	}
	p << osc::EndMessage;
}
//------------------------------------------------------------------------

