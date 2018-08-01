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
}


void Syphon::setup(){

    syphon.setup();
    syphon.set( name , app );
    
    syphon.getTexture();
  
}

void Syphon::update(){
    
    // cout << "syphon" << name <<  " / " << app << " updating" << endl;
    
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
    return width = syphon.getTexture().getWidth();
}

float Syphon::getHeight() {
    return height = syphon.getTexture().getHeight();
}
    
    
} // namespace Sources

