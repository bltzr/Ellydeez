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
        SerialDevice::setup( name );
          
    }
    
    void OSC2APA102::update() {
        
        cout << "updating OSC2APA102" << endl;
        
        // Get the global brightness (aka FastLED "dither")
        if ( brightXpos >= 0 && brightXpos >= 0 )
            brightness = source -> getPixelChannelValue(brightXpos, brightYpos, brightChan);
        sendValueAsIntMessage("/b", brightness);
        
        for ( auto l : allLines ) { l->udpate(); }
        
        for ( auto l : ledLines ) {
            sendValueAsIntMessage( l.first, l.second.getBrightness());
            sendPixelsAsBlobMessage(l.first, l.second.getPixels(), l.second.getNumberOfBytes());
        }
        
        for ( auto l : dmxLines ) {
            sendPixelsAsBlobMessage(l.first, l.second.getPixels(), l.second.getNumberOfBytes());
        }
        
        
        // Make an OSC bundle witt all previous messages and send it to the serial device
        sendPacket( protocols::OSCBundle2ByteBuffer( fetchBundle() ) ); }

} // namespace Sinks{
    

