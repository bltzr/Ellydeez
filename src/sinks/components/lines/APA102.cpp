//
//  APA102Line.cpp
//  Ellydeez
//
//  Created by Pascal Baltazar on 15/07/2018.
//

#include "APA102.hpp"

namespace Sinks {
namespace Lines {
    

    APA102::APA102( ofJson& params  ):
    Line{ params },
    brightXpos{-1},
    brightYpos{-1},
    brightChan{0}
    {
        if ( params[ "brightness" ].is_null() ) {  brightness = 255; }
        else if ( params[ "brightness" ].is_number() ) brightness = int( params[ "brightness" ]);
        else if ( params[ "brightness" ].is_object() ){
            auto& bParams = params[ "brightness" ];
            brightXpos = ( bParams.count( "Xpos" ) ) ? int(bParams[ "Xpos" ]) : 0 ;
            brightYpos = ( bParams.count( "Ypos" ) ) ? int(bParams[ "Ypos" ]) : 0 ;
            brightChan = ( bParams.count( "channel" ) ) ? int(bParams[ "channel" ]) : 0 ;
            source -> checkSize( brightXpos, brightYpos );
        }
    }


void APA102::update() {

    //cout << "actually updating APA102Line" << endl;
    
     if ( brightXpos >= 0 && brightXpos >= 0 ) {
         brightness = source -> getPixelChannelValue(brightXpos, brightYpos, brightChan);
     }
    
    fetchPixelsfromSource();

    for (int i = 0; i < width; ++i){
        for (int j = 0; j < height; ++j){
            for (int c = 0; c < getNumChannels(); ++c ){
                int pos = ( j* width + i ) * getNumChannels() + c ;
                pixels[ pos ] = pixels[ pos ] * mapCol[ brightness ] / 255;
            }
        }
    }
    

}

    
} // namespace Lines 
} // namespace Sinks
