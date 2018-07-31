//
//  Pool.cpp
//  Ellydeez
//
//  Created by Pascal Baltazar on 11/07/2018.
//

#include "Pool.hpp"

Pool::Pool(string name, ofJson& params):
poolName{name}
{
    width =  ( params.count( "width" ) )  ? int(params[ "width" ]) : 1 ;
    height = ( params.count( "height" ) ) ? int(params[ "height" ]) : 0 ;
    setPixelFormatFromString( ( params.count( "format" ) ) ? params[ "format" ] : "RGB" ) ;
    pixels.allocate(width, height, pixFormat);
}

bool Pool::checkFormat ( Pixel::Format format ){
    if (format > m_format ) { m_format = format; return false; }
    return true;
}

void Pool::setPixelFormatFromString(  string format) {
    if      ( format == "RGBA" || format == "RGB_ALPHA" )   setPixelFormat( Pixel::Format::RGBA );
    else if ( format == "RGBA" || format == "RGB_ALPHA" )   setPixelFormat( Pixel::Format::RGB );
    else if ( format == "WA"   || format == "GRAY_ALPHA" )  setPixelFormat( Pixel::Format::WA );
    else if ( format == "W"    || format == "GRAY" )        setPixelFormat( Pixel::Format::W );
    else    setPixelFormat( Pixel::Format::NONE );
    
}

void Pool::setPixelFormat( Pixel::Format format ){
    m_format = format;
    if      ( m_format == Pixel::Format::RGBA )  {pixFormat=OF_PIXELS_RGBA;       nChannels = 4; GLFormat = GL_RGBA; disableAlpha = 0;}
    else if ( m_format == Pixel::Format::RGB )   {pixFormat=OF_PIXELS_RGB; ;      nChannels = 3; GLFormat = GL_RGB;  disableAlpha = 1;}
    else if ( m_format == Pixel::Format::WA )    {pixFormat=OF_PIXELS_GRAY_ALPHA; nChannels = 2; GLFormat = GL_RGBA; disableAlpha = 0;}
    else if ( m_format == Pixel::Format::W )     {pixFormat=OF_PIXELS_GRAY;       nChannels = 1; GLFormat = GL_RGB;  disableAlpha = 1;}
}



void Pool::setActiveSource(Source* src) {
    
    activeSource = src;
    
    /// TODO: get format from source and act accordingly
    
    
    // If the size or pixel formats differ, then we need to pass through a FBO, so let's initialize it first:
    if ( ! direct ) {
        fbo.allocate(width, height, GLFormat);
        fbo.begin();
        if (disableAlpha) ofDisableAlphaBlending();
        ofClear(0,0,0);
        fbo.end();
    }
}

bool Pool::checkSize( float w, float h ) {
    bool res = true;
    if ( w > width ) { width = w; res = false; }
    if ( h > height ) { height = h; res = false; }
    if ( ! res ) direct = ( width == activeSource -> getWidth() && height == activeSource -> getHeight() ) ? true : false ;
    return res;
}

void Pool::update() {
    
    if ( activeSource ) {
        
        if ( direct ) {
            
            pixels = activeSource -> getPixels();
            
        } else {

            fbo.begin();
            if (disableAlpha) ofDisableAlphaBlending();
            activeSource -> draw(0, 0, width, height);
            fbo.end();

            fbo.readToPixels(pixels);
            
        }
        
        activeSource -> update();
        pixels = activeSource -> getPixels();
    }
}

uint8_t Pool::getPixelChannelValue(int Xpos, int Ypos, int channel){
    return pixels [ ( Xpos + Ypos * width ) * nChannels + channel ] ;
}

int Pool::getPixelSummedValue(int Xpos, int Ypos){
    int res { 0 };
    int pos = ( Xpos + Ypos * width ) * nChannels;
    for (int i = 0; i < nChannels; ++i) res += pixels [ pos  + i ];
    return res;
}



void Pool::draw() {
    fbo.draw( 0 ,0, width, height );
}

void Pool::addSource( string srcName, Source* src ) {
    poolSources[ srcName ] = src  ;
}

void Pool::removeSource( string srcName ) {
    poolSources.erase( srcName );
}

void Pool::moveSourceTo( string srcName, Pool* dstPool ){
    //if ( poolSources[ srcName ] ) {
      //  dstPool -> addSource ( srcName, poolSources[ srcName ] );
        //poolSources.erase( srcName );
    //}
}
