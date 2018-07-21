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
        
    cout << "syphon updating" << endl;
    
    // If the source dimensions change,
    if ( ( syphon.getTexture().getWidth() != 0 && syphon.getTexture().getHeight() != 0)
         && ( width != syphon.getTexture().getWidth() || height != syphon.getTexture().getHeight() ) )
        
        // We get the new size
        {
            cout << "Syphon Input: width/height: " << syphon.getTexture().getWidth() << " " << syphon.getTexture().getHeight() << endl;
            width=syphon.getTexture().getWidth();
            height=syphon.getTexture().getHeight();
            
            fbo.allocate(width, height, GLFormat);
            fbo.begin();
            if (disableAlpha) ofDisableAlphaBlending();
            ofClear(0,0,0);
            fbo.end();
        }
        
        // and  we reallocate the FBO to the right sizes
        fbo.begin();
        if (disableAlpha) ofDisableAlphaBlending();
        syphon.draw(0, 0, width, height);
        fbo.end();
        
    }
    
    ofPixels& Syphon::getPixels() {
        
        return pixels;
        
    }
    
} // namespace Sources

