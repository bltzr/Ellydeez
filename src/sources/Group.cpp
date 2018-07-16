//
//  Group.cpp
//  Ellydeez
//
//  Created by Pascal Baltazar on 11/07/2018.
//

#include "Group.hpp"

uint8_t Group::getPixelChannelValue(int Xpos, int Ypos, int channel){
    return pixels [ ( Xpos + Ypos * Xsize ) * nChannels + channel ] ;
}

int Group::getPixelSummedValue(int Xpos, int Ypos){
    int res { 0 };
    int pos = ( Xpos + Ypos * Xsize ) * nChannels;
    for (int i = 0; i < nChannels; ++i) {
        res += pixels [ pos  + i ];
    }
    return res;
}

void Group::setPixelFormat(std::string fmt){
    if      (fmt=="RGBA") {pixFormat=OF_PIXELS_RGBA;       nChannels = 4;}
    else if (fmt==  "BW") {pixFormat=OF_PIXELS_GRAY;       nChannels = 1;}
    else if (fmt== "BWA") {pixFormat=OF_PIXELS_GRAY_ALPHA; nChannels = 2;}
    else                  {pixFormat=OF_PIXELS_RGB; ;      nChannels = 3;}
}
