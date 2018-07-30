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
    setPixelFormat( format = ( params.count( "format" ) ) ? params[ "format" ] : "RGB" ) ;
    pixels.allocate(width, height, pixFormat);
}

void Pool::setPixelFormat(std::string fmt){
    if      ( fmt=="RGBA" )  {pixFormat=OF_PIXELS_RGBA;       nChannels = 4; GLFormat = GL_RGBA; disableAlpha = 0;}
    else if ( fmt==  "W"  )  {pixFormat=OF_PIXELS_GRAY;       nChannels = 1; GLFormat = GL_RGB;  disableAlpha = 1; }
    else if ( fmt== "WA"  )  {pixFormat=OF_PIXELS_GRAY_ALPHA; nChannels = 2; GLFormat = GL_RGBA; disableAlpha = 0;}
    else                     {pixFormat=OF_PIXELS_RGB; ;      nChannels = 3; GLFormat = GL_RGB;  disableAlpha = 1;}
    
}

void Pool::setActiveSource(Source* src) {
    
    activeSource = src;
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
