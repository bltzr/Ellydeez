//
//  ledLine.cpp
//  ledMapper
//
//  Created by Pascal Baltazar on 19/05/2018.
//

#include "ledLine.hpp"


//--------------------------------------------------------------
// Set APA102 Brightness for each LED line:
//
void LedLine::setBrightness(int brightness) {
    
    // check for waiting messages
    
    ofxOscMessage n;
    n.setAddress(address);
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
        dev->dev.send(toEncode);
    } catch ( serial::SerialException e) {
        ofLogError("sendLine") << "failed to send data : " << e.what();
        dev->setup();
    }
    
}

//--------------------------------------------------------------
// Set FastLED Brightness (aka dither) for each LED line:
//
void LedLine::setDither(int dither) {
    
    // check for waiting messages
    
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
        dev->dev.send(toEncode);
    } catch ( serial::SerialException e) {
        ofLogError("sendLine") << "failed to send data : " << e.what();
        dev->setup();
    }
    
}

//--------------------------------------------------------------
// Send the whole thing to each LED line:
//
void LedLine::sendLine() {
    
    src->cropTo(pixelCrop, 0, Yoffset, Xsize, Ysize);
    
    ofBuffer imgAsBuffer;
    imgAsBuffer.clear();
    imgAsBuffer.append((const char*)pixelCrop.getData(),nbPix*3);
    
    ofxOscMessage m;
    m.setAddress(address);
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
        dev->dev.send(toEncode);
    } catch ( serial::SerialException e) {
        ofLogError("sendLine") << "failed to send data : " << e.what();
        dev->setup();
    }
}

//--------------------------------------------------------------
// OSC Message Management
//
void LedLine::appendMessage( ofxOscMessage& message, osc::OutboundPacketStream& p )
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
        //    p << message.getArgAsRgbaColor( i );
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

