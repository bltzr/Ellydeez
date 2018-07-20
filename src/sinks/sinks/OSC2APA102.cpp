//
//  OSC2APA102.cpp
//  Ellydeez
//
//  Created by Pascal Baltazar on 13/07/2018.
//

#include <stdio.h>
#include "OSC2APA102.hpp"

namespace Sinks{
    

    void OSC2APA102::setup( ofJson& params ){
        
        if ( params[ "device" ].is_number() ) name = portName(params[ "device" ]) ;
        else if ( params[ "device" ].is_string() ) name = params[ "device" ] ;
        Serial::setup( name );
        
        auto &lines = params[ "lines" ];
        for(auto line = lines.begin(); line!= lines.end(); ++line ){
            add( line.key(), line.value() );
        }
          
    }
    
    void OSC2APA102::update() {
        
        cout << "updating OSC2APA102" << endl;
        
        // Get the global brightness (aka FastLED "dither")
        if ( brightXpos >= 0 && brightXpos >= 0 )
            brightness = source -> getPixelChannelValue(brightXpos, brightYpos, brightChan);
        sendValueAsIntMessage("/b", brightness);
        
        for ( auto& l : allLines ) { cout << "updating " << l.first << endl; l.second->udpate(); }
        
        /*
        for ( auto& l : ledLines ) {
            sendValueAsIntMessage( l.first, l.second.getBrightness());
            sendPixelsAsBlobMessage(l.first, l.second.getPixels(), l.second.getNumberOfBytes());
        }
        
        for ( auto& l : dmxLines ) {
            sendPixelsAsBlobMessage(l.first, l.second.getPixels(), l.second.getNumberOfBytes());
        }
        
        
        // Make an OSC bundle witt all previous messages and send it to the serial device
        sendPacket( Protocols::OSCBundle2ByteBuffer( fetchBundle() ) );
        */
        
    }
    
    void OSC2APA102::add( string lineName, ofJson& params ){
    
        string name = lineName;
        if ( lineName.find( "APA102line." ) == 0) {
            name = "/" + name.erase( 0, 11 );
            ledLines.emplace( name, Lines::APA102( params ) );
            allLines.emplace( lineName, &ledLines[ name ] );
            cout << endl << "APA102line: " << name << endl << setw(4) << params << endl;
            
        } else if ( lineName.find( "DMXline" ) == 0) {
            name = "/DMX";
            dmxLines.emplace( name, Lines::DMX( params ) );
            allLines.emplace( lineName, &dmxLines[ name ] );
            cout << endl << "DMXline: " << name << endl << setw(4) << params << endl;
            
        } else {ofLogError("OSC2APA102 config: ") << "unknown line type: " << name;}
    }

} // namespace Sinks{
    

