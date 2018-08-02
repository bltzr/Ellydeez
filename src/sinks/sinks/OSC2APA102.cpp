//
//  OSC2APA102.cpp
//  Ellydeez
//
//  Created by Pascal Baltazar on 13/07/2018.
//

#include "OSC2APA102.hpp"

namespace Sinks{

OSC2APA102::OSC2APA102( ofJson& params ):
Serial(),
OSC()
{
 setup ( params );
}

void OSC2APA102::setup( ofJson& params ){

    // setting serial device
    if ( params[ "device" ].is_number() ) name = portName(params[ "device" ]) ;
    else if ( params[ "device" ].is_string() ) name = params[ "device" ] ;
    Serial::setup( name );
    
    // adding lines
    auto &lines = params[ "lines" ];
    for(auto line = lines.begin(); line != lines.end(); ++line ){
        add( line.key(), line.value() );
    }
    
    // Set pool, pixel format, and check that they match
    source = pools[ params[ "source"] ];
    setPixelFormatFromString( ( params.count( "format" ) ) ? params[ "format" ] : "RGB" );
    source -> checkPixelFormat( getPixelFormat() );
    
    // setting appropriate pool for each line (we assume pools have been constructed)
    for (auto& l : allLines) {
        auto* ln = l.second;
        auto* pl = pools[ params["lines"][l.first]["source"] ];
        ln -> setPool( pl ) ;
        // check that the line won't try to fetch pixels over the pool's size, resize it if needed
        pl -> checkSize( ln -> getXpos() + ln -> getWidth() - 1, ln -> getXpos() + ln -> getHeight() - 1 );
        pl -> checkPixelFormat( ln -> getPixelFormat() );
    }
    
    for (auto& l : ledLines ) {
        auto& ln = l.second;
        ln.getPool() -> checkSize( l.second.getBrightXpos(), l.second.getBrightYpos() );
        ln.getPool() -> checkPixelFormat( Pixel::Format(ln.getBrightChan() ) );
    }
    
    // setting brightness params
    if ( params[ "brightness" ].is_null() ) { brightness = 255; }
    else if ( params[ "brightness" ].is_number() ) brightness = int( params[ "brightness" ]);
    else if ( params[ "brightness" ].is_object() ){
        auto& bParams = params[ "brightness" ];
        brightXpos = ( bParams.count( "Xpos" ) ) ? int(bParams[ "Xpos" ]) : 0 ;
        brightYpos = ( bParams.count( "Ypos" ) ) ? int(bParams[ "Ypos" ]) : 0 ;
        brightChan = ( bParams.count( "channel" ) ) ? int(bParams[ "channel" ]) : 0 ;
        source -> checkSize ( brightXpos, brightYpos );
        source -> checkPixelFormat( Pixel::Format( brightChan ) );
    }
}

void OSC2APA102::update() {
    
    //cout << "updating OSC2APA102" << endl;
    
    // Get the global brightness (aka FastLED "dither")
    
    if ( brightXpos >= 0 && brightXpos >= 0 )
        brightness = source -> getPixelChannelValue(brightXpos, brightYpos, brightChan);
    //sendValueAsIntMessage("/b", brightness);
    
    
    for ( auto& l : allLines ) { l.second->update(); }
    
    
    for ( auto& l : ledLines ) {
        //sendValueAsIntMessage( "/"+l.first, l.second.getBrightness());
        //sendPixelsAsBlobMessage(l.first, l.second.getPixels(), l.second.getNumberOfBytes());
    }
    
    for ( auto& l : dmxLines ) {
        //sendPixelsAsBlobMessage( "/"+l.first, l.second.getPixels(), l.second.getNumberOfBytes());
    }
    
    
    // Make an OSC bundle with all previous messages and send it to the serial device
    //sendPacket( Protocols::OSCBundle2ByteBuffer( fetchBundle() ) );
    
    
}
    
void OSC2APA102::addPools(map< string, Pool* >& sourcePools) {
    for (auto& pool : sourcePools)
        pools[ pool.first ] = pool.second;
}

void OSC2APA102::setPool( Pool* sourcePool ) {
    source = sourcePool;
    for (auto& l : allLines) {
        l.second -> setPool( sourcePool ) ;
    }
}

 void OSC2APA102::setPool( ofJson& params ) {
     source = pools[ params[ "source" ] ];
     for (auto& l : allLines) {
         l.second -> setPool( pools[ params["lines"][l.first]["source"] ] ) ;
     }
}
    
void OSC2APA102::add( string lineName, ofJson& params ){

    string name = lineName;
    
    if ( lineName.find( "APA102line." ) == 0) {
        name.erase( 0, 11 );
        ledLines.emplace( name, Lines::APA102( params ) );
        allLines[ lineName ] = &ledLines[ name ] ;
        cout << endl << "APA102line: " << name << endl << setw(4) << params << endl;
        allLines[ lineName ] -> setPool( pools[ params[ "source" ] ] );
        
    } else if ( lineName.find( "DMXline" ) == 0) {
        name = "DMX";
        dmxLines.emplace( name, Lines::DMX( params ) );
        allLines[ lineName ] = &dmxLines[ name ] ;
        cout << endl << "DMXline: " << name << endl << setw(4) << params << endl;
        allLines[ lineName ] -> setPool( pools[ params[ "source" ] ] );
        
    } else {ofLogError("OSC2APA102 config: ") << "unknown line type: " << name;}
}

} // namespace Sinks{
    

