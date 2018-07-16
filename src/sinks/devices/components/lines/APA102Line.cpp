//
//  APA102Line.cpp
//  Ellydeez
//
//  Created by Pascal Baltazar on 15/07/2018.
//

#include "APA102Line.hpp"

namespace Sinks {

void APA102Line::update() {
    
    bright = source -> getPixelChannelValue(brightXpos, brightYpos, brightChan); 
    
    fetchPixelsfromSource();

    for (int i = 0; i < Xsize; ++i){
        for (int j = 0; j < Ysize; ++j){
            for (int c = 0; c < getNumChannels(); ++c ){
                int pos = ( j* Xsize + i ) * getNumChannels() + c ;
                pixels[ pos ] = pixels[ pos ] * mapCol[ bright ] / 255;
            }
        }
    }

}

    
} // namespace Sinks
