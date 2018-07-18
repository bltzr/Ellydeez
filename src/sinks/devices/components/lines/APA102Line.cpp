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

    for (int i = 0; i < width; ++i){
        for (int j = 0; j < height; ++j){
            for (int c = 0; c < getNumChannels(); ++c ){
                int pos = ( j* width + i ) * getNumChannels() + c ;
                pixels[ pos ] = pixels[ pos ] * mapCol[ bright ] / 255;
            }
        }
    }

}

    
} // namespace Sinks
