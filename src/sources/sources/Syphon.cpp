//
//  Syphon.cpp
//  Ellydeez
//
//  Created by Pascal Baltazar on 12/07/2018.
//

#include "Syphon.hpp"

namespace Sources {
    
Syphon::Syphon( ofJson& params ):
Source( )
{
    name = ( params.count( "name" ) ) ? params[ "name" ] : "" ;
    app = ( params.count( "app" ) ) ? params[ "app" ] : "Simple Server" ;
    width = ( params.count( "width" ) ) ? int(params[ "width" ]) : 1 ;
    height = ( params.count( "height" ) ) ? int(params[ "height" ]) : 0 ;
    format = ( params.count( "format" ) ) ? params[ "format" ] : "RGB" ;
}


void Syphon::setup(){

    syphon.setup();
    syphon.set( name , app );
    
    if (pixFormat == OF_PIXELS_RGB || pixFormat == OF_PIXELS_GRAY)
         {GLFormat = GL_RGB;  disableAlpha = 1;}
    else {GLFormat = GL_RGBA; disableAlpha = 0;}
    
    // FBO init
    fbo.allocate(width, height, GLFormat);
    fbo.begin();
    if (disableAlpha) ofDisableAlphaBlending();
    ofClear(0,0,0,0);
    fbo.end();
    
}

void Syphon::update(){
    
    cout << "syphon" << name <<  " / " << app << " updating" << endl;
    
    //syphon.getTexture().readToPixels(pixels);
    
}

void Syphon::draw (float x, float y, float w, float h) {
    syphon.draw( x, y, w, h);
}
    
ofPixels& Syphon::getPixels() {
    syphon.getTexture().readToPixels(pixels);
    return pixels;
}

float Syphon::getWidth() {
    return syphon.getTexture().getWidth();
}

float Syphon::getHeight() {
    return syphon.getTexture().getHeight();
}
    
    
} // namespace Sources

