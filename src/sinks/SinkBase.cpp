//
//  SinkBase.cpp
//  Ellydeez
//
//  Created by Pascal Baltazar on 13/07/2018.
//

#include "SinkBase.hpp"




void Sink::setPixelFormatFromString(  string format) {
    if      ( format == "RGBA" || format == "RGB_ALPHA" )   setPixelFormat( Pixel::Format::RGBA );
    else if ( format == "RGBA" || format == "RGB_ALPHA" )   setPixelFormat( Pixel::Format::RGB );
    else if ( format == "WA"   || format == "GRAY_ALPHA" )  setPixelFormat( Pixel::Format::WA );
    else if ( format == "W"    || format == "GRAY" )        setPixelFormat( Pixel::Format::W );
    else    setPixelFormat( Pixel::Format::NONE );
    
}

void Sink::setPixelFormat( Pixel::Format format ){
    m_format = format;
    if      ( m_format == Pixel::Format::RGBA )  {pixFormat=OF_PIXELS_RGBA;  }
    else if ( m_format == Pixel::Format::RGB )   {pixFormat=OF_PIXELS_RGB; }
    else if ( m_format == Pixel::Format::WA )    {pixFormat=OF_PIXELS_GRAY_ALPHA; }
    else if ( m_format == Pixel::Format::W )     {pixFormat=OF_PIXELS_GRAY;      }
}

