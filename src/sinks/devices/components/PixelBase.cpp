//
//  PixelBase.cpp
//  Ellydeez
//
//  Created by Pascal Baltazar on 15/07/2018.
//

#include "PixelBase.hpp"

namespace Sinks {
    
uint8_t PixelBase::getValue(){
    return source->getPixels() [ ( Xpos + Ypos * source->getWidth() ) * pixMult + pixPos ] ;
}

void PixelBase::setPixelFormat(std::string fmt){
    if     (fmt=="RGBA") {pixFormat=OF_PIXELS_RGBA;       pixMult = 4;}
    else if  (fmt=="W") {pixFormat=OF_PIXELS_GRAY;       pixMult = 1;}
    else if (fmt=="WA") {pixFormat=OF_PIXELS_GRAY_ALPHA; pixMult = 2;}
    else                 {pixFormat=OF_PIXELS_RGB; ;      pixMult = 3;}
}
    
} // namespace Sinks
