//
//  OSC2APA102.cpp
//  Ellydeez
//
//  Created by Pascal Baltazar on 13/07/2018.
//

#include <stdio.h>
#include "OSC2APA102.hpp"

namespace Sinks{
    
    void OSC2APA102::sendOSCBundle() {
        
        // this code comes from ofxOscSender::sendMessage in ofxOscSender.cpp
        static const int OUTPUT_BUFFER_SIZE = 16384;
        char buffer[OUTPUT_BUFFER_SIZE];
        osc::OutboundPacketStream packet ( buffer, OUTPUT_BUFFER_SIZE );

        // serialise the message
        packet << osc::BeginBundleImmediate;
        
        // Add all OSC messages here:
        for (auto l : outLines){
            for (auto m : l->OSCmessages){
                appendOSCMessage(packet, m);
            }
        }
        
        
        // close the bundle
        packet << osc::EndBundle;
        
        ofx::IO::ByteBuffer toEncode(packet.Data(),packet.Size());
        
        try {
            send(toEncode);
        } catch ( serial::SerialException e) {
            ofLogError("sendLine") << "failed to send data : " << e.what();
            reconnect();
        }
        
    }
    
    void OSC2APA102::appendOSCMessage(osc::OutboundPacketStream& packet, ofxOscMessage& message)
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

} // namespace Sinks{
    

