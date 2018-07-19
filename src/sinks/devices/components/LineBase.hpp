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
 
class LineBase {
    
public:
    
    virtual void setup();
    virtual void udpate() { fetchPixelsfromSource(); }
    virtual void draw();
    virtual void exit();
    
    const ofPixels& getPixels();
    
    string  getPixelFormat() { return format; }
    
    int     getNumChannels() { return nChannels; }
    
    int     getNumberOfPixels()    { return nPix;}
    int     getNumberOfBytes()     { return nBytes;}
    
protected:
    
    LineBase(Pool* pool,
             int sizeX = 1, int sizeY = 0,
             int OffsetX = 0, int offsetY = 0,
             string pixelFormat = "RGB",
             int nPixels = 0):
    source{pool},
    width{sizeX},
    height{sizeY},
    Xoffset{OffsetX},
    Yoffset{offsetY},
    format{pixelFormat},
    nPix{nPixels}
    {
        if (format!="RGB") setPixelFormat(format);
            if (nPix==0) {
                nPix = width*height;
                nBytes = nPix*3;
            }
    }
    
    ~LineBase() = default;
    
    void            setPixelFormat( string fmt );
    
    virtual void    fetchPixelsfromSource();
    
    Pool *         source;         // source pool

    int             width = 1;       // X length of the line
    int             height = 0;       // how many lines to include
    int             Xoffset = 0;     // how many pixels to offset from (X)
    int             Yoffset = 0;     // how many lines to offset from
    
    ofPixels        pixels;         
    
private:
    
    string          format{"RGB"}; // other choices: RGBA, W, WA
    ofPixelFormat   pixFormat{OF_PIXELS_RGB};
    int             nChannels{3};
    
    int             nPix;           // number of pixels
    int             nBytes;          // number of pixels
    
    friend class    ::Sink;
    
};
    
} // namespace Sinks

#endif /* LineBase_hpp */
