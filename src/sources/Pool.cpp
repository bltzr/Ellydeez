//
//  Pool.cpp
//  Ellydeez
//
//  Created by Pascal Baltazar on 11/07/2018.
//

#include "Pool.hpp"

Pool::Pool(ofJson& params)
{
    width =  ( params.count( "width" ) )  ? int(params[ "width" ]) : 1 ;
    height = ( params.count( "height" ) ) ? int(params[ "height" ]) : 0 ;
    setPixelFormatFromString( ( params.count( "format" ) ) ? params[ "format" ] : "RGB" ) ;
    allocate();
}

bool Pool::checkPixelFormat ( Pixel::Format format ){
    if (format > m_format ) { setPixelFormat( format ); return false; }
    return true;
}

void Pool::setPixelFormatFromString(  string format) {
    if      ( format == "RGBA" || format == "RGB_ALPHA" )   setPixelFormat( Pixel::Format::RGBA );
    else if ( format == "RGBA" || format == "RGB_ALPHA" )   setPixelFormat( Pixel::Format::RGB );
    else if ( format == "WA"   || format == "GRAY_ALPHA" )  setPixelFormat( Pixel::Format::WA );
    else if ( format == "W"    || format == "GRAY" )        setPixelFormat( Pixel::Format::W );
    else    setPixelFormat( Pixel::Format::NONE );
}

void Pool::setPixelFormat( Pixel::Format format ) {
    if ( m_format != format ) {
        m_format = format;
        if      ( m_format == Pixel::Format::RGBA )  { pixFormat=OF_PIXELS_RGBA;       nChannels = 4; GLFormat = GL_RGBA; disableAlpha = 0; }
        else if ( m_format == Pixel::Format::RGB )   { pixFormat=OF_PIXELS_RGB; ;      nChannels = 3; GLFormat = GL_RGB;  disableAlpha = 1; }
        else if ( m_format == Pixel::Format::WA )    { pixFormat=OF_PIXELS_GRAY_ALPHA; nChannels = 2; GLFormat = GL_RGBA; disableAlpha = 0; }
        else if ( m_format == Pixel::Format::W )     { pixFormat=OF_PIXELS_GRAY;       nChannels = 1; GLFormat = GL_RGB;  disableAlpha = 1; }
        allocate();
    }
}

void Pool::setActiveSource(Source* src) {
    if ( src && activeSource != src ) {
        activeSource = src;
        float srcW = activeSource -> getWidth();
        float srcH = activeSource -> getHeight();
        if ( srcW > width || srcH > height ) {
            direct = false;
            width = srcW;
            height = srcH;
        }
        if ( activeSource -> getPixelFormat() != m_format ) {
            direct = false;
        }
        cout << "direct ? " << direct << endl;
    }
    allocate();
}

bool Pool::checkSize( float w, float h ) {
    bool res = true;
    if ( w > width ) { width = w; res = false; }
    if ( h > height ) { height = h; res = false; }
    if ( ! res ) {
        direct = ( width == activeSource -> getWidth()
                && height == activeSource -> getHeight() );
        allocate();
    }
    cout << "direct ? " << direct << endl;
    return res;
}

void Pool::update() {
    
    if ( activeSource ) {
        
        activeSource -> update();
        
        if ( direct ) {
            
            pixels = activeSource -> getPixels();
            
        } else {

            fbo.begin();
            if (disableAlpha) ofDisableAlphaBlending();
            activeSource -> draw(0, 0, width, height);
            fbo.end();

            fbo.readToPixels(pixels);
        }
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

void Pool::draw(float x, float y, float w, float h) {
    if ( direct ) {
        texture.loadData( pixels );
    } else {
        fbo.draw( x , y, w, h );
    }
}

void Pool::addSource( string srcName, Source* src ) {
    poolSources[ srcName ] = src  ;
}

void Pool::removeSource( string srcName ) {
    poolSources.erase( srcName );
}

void Pool::allocate() {
    if ( direct ) {
        pixels.allocate(width, height, pixFormat);
        texture.allocate( pixels );
    } else {
        fbo.allocate(width, height, GLFormat);
        fbo.begin();
        if (disableAlpha) {
            ofDisableAlphaBlending();
            ofClear(0,0,0);
        } else { ofClear(0,0,0, 255); }
        fbo.end();
    }
}

