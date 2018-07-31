//
//  Pool.hpp
//  Ellydeez
//
//  Created by Pascal Baltazar on 11/07/2018.
//

#ifndef Pool_hpp
#define Pool_hpp

#include <stdio.h>
#include <map>
#include "ofMain.h"
#include "SourceBase.hpp"
#include "Syphon.hpp"
#include "Player.hpp"
//#include "SourceFactory.hpp"

class SourceFactory;
class Line;

class Pool {
    
public:
    
    Pool() = default;

    Pool(ofJson& params);
    
    ofPixels& getPixels()                   { return pixels; }
    
    uint8_t getPixelChannelValue(int Xpos, int Ypos = 0, int channel = 0);
    int     getPixelSummedValue (int Xpos, int Ypos = 0);
    
    void    setActiveSource(Source* src);
    Source* getActiveSource() const         { return activeSource; }
    
    int     getWidth() const                { return width; }
    int     getHeight() const               { return height; }
    
    // resizes and returns false if passed dimensions exceed current dimensions
    bool    checkSize( float width, float height );
    bool    checkPixelFormat ( Pixel::Format format );
    
    Pixel::Format  getPixelFormat()                { return m_format; }
    
    void update();
    void draw();
    
protected:
    
    void    addSource( string name, Source* src );
    void    removeSource( string name );
    void    moveSourceTo( string name, Pool* dstPool );
    
    void    setPixelFormat( Pixel::Format format );
    void    setPixelFormatFromString( string format );
    
private:
    
    map< string, Source* >  poolSources;

    
    Source*                 activeSource{nullptr};
    ofFbo                   fbo;
    ofPixels                pixels;
    
    
    Pixel::Format             m_format{ Pixel::Format::NONE };
    int                     nChannels{ 3 };
    ofPixelFormat           pixFormat{ OF_PIXELS_RGB };
    int                     GLFormat{ GL_RGB };
    bool                    disableAlpha{ 1 };
    
    int                     width {0};
    int                     height {0};
    bool                    direct {false};
    
    
    friend class            SourceFactory;
    friend class            Sink;
    friend class            Line;

};

#endif /* Pool_hpp */
