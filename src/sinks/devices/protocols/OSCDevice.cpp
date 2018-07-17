//
//  OSCDevice.cpp
//  Ellydeez
//
//  Created by Pascal Baltazar on 14/07/2018.
//

#include "OSCDevice.hpp"

namespace Sinks {
    
void OSCDevice::sendValueAsIntMessage(string addr, int v)
{
    
    ofxOscMessage n;
    n.setAddress(addr);
    n.addIntArg(v);
    OSCmessages.push_back(n);
    
}

void OSCDevice::sendPixelsAsBlobMessage(string addr, const ofPixels& pix, int nBytes)
{
    
    ofBuffer imgAsBuffer;
    imgAsBuffer.clear();
    imgAsBuffer.append((const char*)pix.getData(),nBytes);
    
    ofxOscMessage m;
    m.setAddress(addr);
    m.addBlobArg(imgAsBuffer);
    OSCmessages.push_back(m);
    
}

void OSCDevice::appendOSCMessage(osc::OutboundPacketStream& packet, ofxOscMessage& message)
{
    
    packet << osc::BeginMessage( message.getAddress().c_str() );
    for ( int i=0; i< message.getNumArgs(); ++i )
    {
        if ( message.getArgType(i) == OFXOSC_TYPE_INT32 )
            packet << message.getArgAsInt32( i );
        else if ( message.getArgType(i) == OFXOSC_TYPE_INT64 )
            packet << (osc::int64)message.getArgAsInt64( i );
        else if ( message.getArgType( i ) == OFXOSC_TYPE_FLOAT )
            packet << message.getArgAsFloat( i );
        else if ( message.getArgType( i ) == OFXOSC_TYPE_DOUBLE )
            packet << message.getArgAsDouble( i );
        else if ( message.getArgType( i ) == OFXOSC_TYPE_STRING || message.getArgType( i ) == OFXOSC_TYPE_SYMBOL)
            packet << message.getArgAsString( i ).c_str();
        else if ( message.getArgType( i ) == OFXOSC_TYPE_CHAR )
            packet << message.getArgAsChar( i );
        //else if ( message.getArgType( i ) == OFXOSC_TYPE_MIDI_MESSAGE )
        //  packet << message.getArgAsMidiMessage( i );
        else if ( message.getArgType( i ) == OFXOSC_TYPE_TRUE || message.getArgType( i ) == OFXOSC_TYPE_FALSE )
            packet << message.getArgAsBool( i );
        else if ( message.getArgType( i ) == OFXOSC_TYPE_TRIGGER )
            packet << message.getArgAsTrigger( i );
        else if ( message.getArgType( i ) == OFXOSC_TYPE_TIMETAG )
            packet << (osc::int64)message.getArgAsTimetag( i );
        //else if ( message.getArgType( i ) == OFXOSC_TYPE_RGBA_COLOR )
        //  packet << message.getArgAsRgbaColor( i );
        else if ( message.getArgType( i ) == OFXOSC_TYPE_BLOB ){
            ofBuffer buff = message.getArgAsBlob(i);
            osc::Blob b(buff.getData(), (unsigned long)buff.size());
            packet << b;
        }else
        {
            ofLogError("OSC2APA102") << "appendOSCMessage(): bad argument type " << message.getArgType( i );
            assert( false );
        }
    }
    packet << osc::EndMessage;
    
}

osc::OutboundPacketStream OSCDevice::fetchBundle() {
    
    // this code comes from ofxOscSender::sendMessage in ofxOscSender.cpp
    static const int OUTPUT_BUFFER_SIZE = 16384;
    char buffer[OUTPUT_BUFFER_SIZE];
    osc::OutboundPacketStream packet ( buffer, OUTPUT_BUFFER_SIZE );

    // serialise the message
    packet << osc::BeginBundleImmediate;
    
    // Add all OSC messages here:
    for (auto m : OSCmessages){
        appendOSCMessage(packet, m);
    } // Then clear them
    OSCmessages.clear();
    
    // close the bundle
    packet << osc::EndBundle;
    
    return packet;
    
}
    
    
////////////// Helper Functions: //////////////

ofx::IO::ByteBuffer OSCBundle2ByteBuffer (const osc::OutboundPacketStream& packet ) {
    ofx::IO::ByteBuffer res( packet.Data(), packet.Size() );
    return res;
}
    
    

    
} //namespace Sinks
