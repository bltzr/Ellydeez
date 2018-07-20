//
//  APA102Line.cpp
//  Ellydeez
//
//  Created by Pascal Baltazar on 15/07/2018.
//

#include "APA102Line.hpp"

namespace Sinks {
    
    APA102Line::APA102Line( ofJson& params  ):
    LineBase{ params },
    brightXpos{0},
    brightYpos{0},
    brightChan{0}
    {}

void APA102Line::update() {
    
    
    cout << "updating APA102Line" << endl;
    
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
