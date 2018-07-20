//
//  LineBase.cpp
//  Ellydeez
//
//  Created by Pascal Baltazar on 22/05/2018.
//

#include "LineBase.hpp"


namespace Sinks {
    
    Line::Line( ofJson& params )
    {
        format = ( params.count( "format" ) ) ? params[ "format" ] : "RGB" ;
        if (format!="RGB") setPixelFormat(format);
            if (nPix==0) {
                nPix = width*height;
                nBytes = nPix*3;
            }
    }
    
void Line::fetchPixelsfromSource(){
    source -> getPixels().cropTo( pixels, Xoffset, Yoffset, width, height );
}

const ofPixels& Line::getPixels(){
    return pixels;
}
    
void Line::setPixelFormat(std::string fmt){
    
    if     (fmt=="RGBA") {pixFormat=OF_PIXELS_RGBA;       nChannels = 4;}
    else if  (fmt=="W")  {pixFormat=OF_PIXELS_GRAY;       nChannels = 1;}
    else if (fmt=="WA")  {pixFormat=OF_PIXELS_GRAY_ALPHA; nChannels = 2;}
    else                 {pixFormat=OF_PIXELS_RGB; ;      nChannels = 3;}
    
    nBytes = nPix * nChannels;
    
}

} // namespace Sinks

