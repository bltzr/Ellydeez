//
//  Pool.hpp
//  Ellydeez
//
//  Created by Pascal Baltazar on 11/07/2018.
//

#ifndef Pool_hpp
#define Pool_hpp

#include <stdio.h>
#include <list>
#include "ofMain.h"
//#include "SourceBase.hpp"
//#include "SourceFactory.hpp"

using namespace std;

class SourceFactory;
class Source;
class LineBase;

class Pool {
    
public:

    Pool(string name,
          string pixelFormat = "RGB"):
        poolName{name},
        format{pixelFormat}
        { if (format!="RGB") setPixelFormat(format); }
    
    ofPixels& getPixels()                   { return pixels; }
    
    uint8_t getPixelChannelValue(int Xpos, int Ypos = 0, int pixPos = 0);
    int     getPixelSummedValue (int Xpos, int Ypos = 0);

    string  getName() const                 { return poolName; }
    
    void    setActiveSource(Source* src)    { activeSource = src; }
    Source* getActiveSource() const         { return activeSource; }
    
    int     getXsize()                      { return Xsize; }
    int     getYsize()                      { return Ysize; }
    
    string  getPixelFormat()                { return format; }
    
protected:
    
    void    add(Source*);
    void    remove(Source*);
    void    moveTo(Source*, Pool*);
    
    void    setPixelFormat( std::string fmt );
    
    // if we want to be able to change the name, we must update it
    // in all registered Sources and all client Sinks
    
private:
    
    string              poolName;
    
    list<Source*>       sources;
    Source*             activeSource;
    
    ofPixels            pixels;
    
    string              format{"RGB"}; // other choices: RGBA, BW, BWA
    int                 nChannels{3};
    ofPixelFormat       pixFormat{OF_PIXELS_RGB};
    
    int                 Xsize {0};
    int                 Ysize {0};
    
    
    friend class        SourceFactory;
    friend class        LineBase;

};

#endif /* Pool_hpp */
