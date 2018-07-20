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
    cout << "constructing LineBase with json " << endl;
    width = ( params.count( "width" ) ) ? int(params[ "width" ]) : 1 ;
    height = ( params.count( "height" ) ) ? int(params[ "height" ]) : 0 ;
    Xoffset = ( params.count( "Xoffset" ) ) ? int(params[ "Xoffset" ]) : 0 ;
    Yoffset = ( params.count( "Yoffset" ) ) ? int(params[ "Yoffset" ]) : 0 ;
    format = ( params.count( "format" ) ) ? params[ "format" ] : "RGB" ;
    if (format!="RGB") setPixelFormat(format);
        if (nPix==0) {
            nPix = width*height;
            nBytes = nPix*nChannels;
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

