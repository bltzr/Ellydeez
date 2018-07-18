//
//  Pool.cpp
//  Ellydeez
//
//  Created by Pascal Baltazar on 11/07/2018.
//

#include "Pool.hpp"

uint8_t Pool::getPixelChannelValue(int Xpos, int Ypos, int channel){
    return pixels [ ( Xpos + Ypos * Xsize ) * nChannels + channel ] ;
}

int Pool::getPixelSummedValue(int Xpos, int Ypos){
    int res { 0 };
    int pos = ( Xpos + Ypos * Xsize ) * nChannels;
    for (int i = 0; i < nChannels; ++i) {
        res += pixels [ pos  + i ];
    }
    return res;
}

void Pool::setPixelFormat(std::string fmt){
    if      (fmt=="RGBA") {pixFormat=OF_PIXELS_RGBA;       nChannels = 4;}
    else if (fmt==  "BW") {pixFormat=OF_PIXELS_GRAY;       nChannels = 1;}
    else if (fmt== "BWA") {pixFormat=OF_PIXELS_GRAY_ALPHA; nChannels = 2;}
    else                  {pixFormat=OF_PIXELS_RGB; ;      nChannels = 3;}
    
}
