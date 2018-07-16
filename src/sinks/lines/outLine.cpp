//
//  outLine.cpp
//  Ellydeez
//
//  Created by Pascal Baltazar on 22/05/2018.
//

#include "outLine.hpp"


namespace Sinks {
    
void OutLine::setPixelFormat(std::string fmt){
    if (fmt=="RGBA")     {pixelFormat=OF_PIXELS_RGBA; nBytes = nbPix*4;}
    else if (fmt=="BW")  pixelFormat=OF_PIXELS_GRAY;
    else if (fmt=="BWA") pixelFormat=OF_PIXELS_GRAY_ALPHA;
    else                 pixelFormat=OF_PIXELS_RGB;
    
}

} // namespace Sinks

