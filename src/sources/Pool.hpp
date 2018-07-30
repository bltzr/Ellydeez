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

using namespace std;

class SourceFactory;
class LineBase;

class Pool {
    
public:
    
    Pool() = default;

    Pool(string name, ofJson& params);
    
    ofPixels& getPixels()                   { return pixels; }
    
    uint8_t getPixelChannelValue(int Xpos, int Ypos = 0, int channel = 0);
    int     getPixelSummedValue (int Xpos, int Ypos = 0);

    string  getName() const                 { return poolName; }
    
    void    setActiveSource(Source* src);
    Source* getActiveSource() const         { return activeSource; }
    
    int     getWidth()                      { return width; }
    int     getHeight()                     { return height; }
    
    // resizes and returns false if passed dimensions exceed current dimensions
    bool    checkSize( float width, float height );
    
    string  getPixelFormat()                { return format; }
    
    void update();
    void draw();
    
protected:
    
    void    addSource( string name, Source* src );
    void    removeSource( string name );
    void    moveSourceTo( string name, Pool* dstPool );
    
    void    setPixelFormat( std::string fmt );

    // if we want to be able to change the name, we must update it
    // in all registered Sources and all client Sinks
    
private:
    
    string                  poolName;
    
    map< string, Source* >  poolSources;

    
    Source*                 activeSource{nullptr};
    ofFbo                   fbo;
    ofPixels                pixels;
    
    
    string                  format{"RGB"}; // other choices: RGBA, W, WA
    int                     nChannels{3};
    ofPixelFormat           pixFormat{OF_PIXELS_RGB};
    int                     GLFormat{GL_RGB};
    bool                    disableAlpha{1};
    
    int                     width {0};
    int                     height {0};
    bool                    direct {false};
    
    
    friend class            SourceFactory;
    friend class            LineBase;

};

#endif /* Pool_hpp */
