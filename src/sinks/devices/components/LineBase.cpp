//
//  LineBase.cpp
//  Ellydeez
//
//  Created by Pascal Baltazar on 22/05/2018.
//

#include "LineBase.hpp"


namespace Sinks {
    
ofPixels& LineBase::getPixels(){
    source->getPixels().cropTo(pixels, Xoffset, Yoffset, Xsize, Ysize);
    return pixels;
}

void LineBase::setPixelFormat(std::string fmt){
    if     (fmt=="RGBA") {pixelFormat=OF_PIXELS_RGBA;       nBytes = nPix*4;}
    else if  (fmt=="BW") {pixelFormat=OF_PIXELS_GRAY;       nBytes = nPix;}
    else if (fmt=="BWA") {pixelFormat=OF_PIXELS_GRAY_ALPHA; nBytes = nPix*2;}
    else                 {pixelFormat=OF_PIXELS_RGB; ;      nBytes = nPix*3;}
    
}

} // namespace Sinks

