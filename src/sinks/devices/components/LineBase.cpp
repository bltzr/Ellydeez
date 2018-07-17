//
//  LineBase.cpp
//  Ellydeez
//
//  Created by Pascal Baltazar on 22/05/2018.
//

#include "LineBase.hpp"


namespace Sinks {
    
void LineBase::fetchPixelsfromSource(){
    source -> getPixels().cropTo( pixels, Xoffset, Yoffset, Xsize, Ysize );
}

const ofPixels& LineBase::getPixels(){
    return pixels;
}
    
void LineBase::setPixelFormat(std::string fmt){
    
    if     (fmt=="RGBA") {pixFormat=OF_PIXELS_RGBA;       nChannels = 4;}
    else if  (fmt=="BW") {pixFormat=OF_PIXELS_GRAY;       nChannels = 1;}
    else if (fmt=="BWA") {pixFormat=OF_PIXELS_GRAY_ALPHA; nChannels = 2;}
    else                 {pixFormat=OF_PIXELS_RGB; ;      nChannels = 3;}
    
    nBytes = nPix * nChannels;
    
}

} // namespace Sinks

