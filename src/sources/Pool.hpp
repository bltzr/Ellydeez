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
    
    void    setActiveSource(Source* src)    { activeSource = src; }
    Source* getActiveSource() const         { return activeSource; }
    
    int     getWidth()                      { return width; }
    int     getHeight()                     { return height; }
    
    string  getPixelFormat()                { return format; }
    
protected:
    
    void    addSource( string name, Source* src );
    void    removeSource( string name );
    void    moveSourceTo( string name, Pool* dstPool );
    
    void    setPixelFormat( std::string fmt );
    

    
    // if we want to be able to change the name, we must update it
    // in all registered Sources and all client Sinks
    
private:
    
    list< Source* >         poolSources;
    
    string                  poolName;
    
    
    Source*                 activeSource{nullptr};
    
    ofPixels                pixels;
    
    
    string                  format{"RGB"}; // other choices: RGBA, W, WA
    int                     nChannels{3};
    ofPixelFormat           pixFormat{OF_PIXELS_RGB};
    
    int                     width {0};
    int                     height {0};
    
    
    friend class            SourceFactory;
    friend class            LineBase;

};

#endif /* Pool_hpp */
