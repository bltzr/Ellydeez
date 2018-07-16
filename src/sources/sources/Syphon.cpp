//
//  Syphon.cpp
//  Ellydeez
//
//  Created by Pascal Baltazar on 12/07/2018.
//

#include "Syphon.hpp"

namespace Sources {
    
    void Syphon::setup(){

        client.setup();
        client.set( name , app );
        
        if (pixelFormat == OF_PIXELS_RGB || pixelFormat == OF_PIXELS_GRAY)
             {GLFormat = GL_RGB;  disableAlpha = 1;}
        else {GLFormat = GL_RGBA; disableAlpha = 0;}
        
        // FBO init
        fbo.allocate(Xsize, Ysize, GLFormat);
        fbo.begin();
        if (disableAlpha) ofDisableAlphaBlending();
        ofClear(0,0,0,0);
        fbo.end();
        
    }
    
    void Syphon::update(){
    
    // If the source dimensions change,
    if ((client.getTexture().getWidth()!=0&&client.getTexture().getHeight()!=0)
        &&(Xsize!=client.getTexture().getWidth() ||
           Ysize!=client.getTexture().getHeight()))
        
        // We get the new size
        {
            cout << "Syphon Input: width/height: " << client.getTexture().getWidth() << " " << client.getTexture().getHeight() << endl;
            Xsize=client.getTexture().getWidth();
            Ysize=client.getTexture().getHeight();
            
            fbo.allocate(Xsize, Ysize, GLFormat);
            fbo.begin();
            if (disableAlpha) ofDisableAlphaBlending();
            ofClear(0,0,0);
            fbo.end();
        }
        
        // and  we reallocate the FBO to the right sizes
        fbo.begin();
        if (disableAlpha) ofDisableAlphaBlending();
        client.draw(0, 0, Xsize, Ysize);
        fbo.end();
        
    }
    
    ofPixels& Syphon::getPixels() {
        
        fbo.readToPixels(pixels);
        return pixels;
        
    }
    
} // namespace Sources

