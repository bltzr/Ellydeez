//
//  Syphon.cpp
//  Ellydeez
//
//  Created by Pascal Baltazar on 12/07/2018.
//

#include "Syphon.hpp"

namespace Sources {
    
    void Syphon::setup(){

        mClient.setup();
        mClient.set( name , app );
        
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
    
    // If the source dimensions change, we reallocate the FBO to the right sizes
    if ((mClient.getTexture().getWidth()!=0&&mClient.getTexture().getHeight()!=0)
        &&(Xsize!=mClient.getTexture().getWidth() ||
           Ysize!=mClient.getTexture().getHeight())){
            cout << "Syphon Input: width/height: " << mClient.getTexture().getWidth() << " " << mClient.getTexture().getHeight() << endl;
            Xsize=mClient.getTexture().getWidth();
            Ysize=mClient.getTexture().getHeight();
            fbo.allocate(Xsize, Ysize, GLFormat);
            fbo.begin();
            if (disableAlpha) ofDisableAlphaBlending();
            ofClear(0,0,0);
            fbo.end();
        }
        
        fbo.begin();
        if (disableAlpha) ofDisableAlphaBlending();
        mClient.draw(0, 0, Xsize, Ysize);
        fbo.end();
        
    }
    
    ofPixels& Syphon::getPixels() {
        
        fbo.readToPixels(pixels);
        return pixels;
        
    }
    
} // namespace Sources

