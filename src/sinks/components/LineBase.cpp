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
    width = ( params.count( "width" ) ) ? int(params[ "width" ]) : 1 ;
    height = ( params.count( "height" ) ) ? int(params[ "height" ]) : 0 ;
    Xpos = ( params.count( "Xpos" ) ) ? int(params[ "Xpos" ]) : 0 ;
    Ypos = ( params.count( "Ypos" ) ) ? int(params[ "Ypos" ]) : 0 ;
    string format = ( params.count( "format" ) ) ? params[ "format" ] : "RGB" ;
    if (format!="RGB") setPixelFormatFromString(format);
        if (nPix==0) {
            nPix = width*height;
            nBytes = nPix*nChannels;
        }
}

void Line::setPixelFormatFromString(  string format) {
    if      ( format == "RGBA" || format == "RGB_ALPHA" )   setPixelFormat( Pixel::Format::RGBA );
    else if ( format == "RGBA" || format == "RGB_ALPHA" )   setPixelFormat( Pixel::Format::RGB );
    else if ( format == "WA"   || format == "GRAY_ALPHA" )  setPixelFormat( Pixel::Format::WA );
    else if ( format == "W"    || format == "GRAY" )        setPixelFormat( Pixel::Format::W );
    else    setPixelFormat( Pixel::Format::NONE );
    
}

void Line::setPixelFormat( Pixel::Format format ){
    m_format = format;
    if      ( m_format == Pixel::Format::RGBA )  {pixFormat=OF_PIXELS_RGBA;       nChannels = 4;}
    else if ( m_format == Pixel::Format::RGB )   {pixFormat=OF_PIXELS_GRAY;       nChannels = 1;}
    else if ( m_format == Pixel::Format::WA )    {pixFormat=OF_PIXELS_GRAY_ALPHA; nChannels = 2;}
    else if ( m_format == Pixel::Format::W )     {pixFormat=OF_PIXELS_RGB; ;      nChannels = 3;}
    
    nBytes = nPix * nChannels;
}
    
void Line::fetchPixelsfromSource(){
    source -> getPixels().cropTo( pixels, Xpos, Ypos, width, height );
}

const ofPixels& Line::getPixels(){
    return pixels;
}
    

} // namespace Sinks

