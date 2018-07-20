//
//  LineBase.hpp
//  Ellydeez
//
//  Created by Pascal Baltazar on 22/05/2018.
//

#ifndef LineBase_hpp
#define LineBase_hpp

#include <vector>
#include "ofMain.h"
#include "Pool.hpp"

using namespace std;

class Sink;

namespace Sinks {
 
class Line {
    
public:
    
    virtual void setup() {}
    virtual void udpate() { cout << "updating LineBase" << endl; }
    virtual void draw() {}
    virtual void exit() {}
    
    const ofPixels& getPixels();
    
    string  getPixelFormat() { return format; }
    
    int     getNumChannels() { return nChannels; }
    
    int     getNumberOfPixels()    { return nPix;}
    int     getNumberOfBytes()     { return nBytes;}
    
protected:
    
    Line() = default;
    
    Line( ofJson& params );

    virtual ~Line() = default;
    
    void    setPixelFormat( string fmt );
    
    void    fetchPixelsfromSource();
    
    
    Pool *          source;         // source pool

    int             width = 1;       // X length of the line
    int             height = 0;       // how many lines to include
    int             Xoffset = 0;     // how many pixels to offset from (X)
    int             Yoffset = 0;     // how many lines to offset from
    
    ofPixels        pixels;         
    
private:
    
    string          format{"RGB"}; // other choices: RGBA, W, WA
    ofPixelFormat   pixFormat{OF_PIXELS_RGB};
    int             nChannels{3};
    
    int             nPix{0};           // number of pixels
    int             nBytes{0};          // number of pixels
    
    friend class    ::Sink;
    
};
    
} // namespace Sinks

#endif /* LineBase_hpp */
