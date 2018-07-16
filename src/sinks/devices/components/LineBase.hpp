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
#include "Group.hpp"

using namespace std;

class Sink;

namespace Sinks {
 
class LineBase {
    
public:
    
    virtual void setup();
    virtual void udpate();
    virtual void draw();
    virtual void exit();
    
protected:
    
    LineBase(Group* group,
             int sizeX = 1, int sizeY = 0,
             int OffsetX = 0, int offsetY = 0,
             string pixel_format = "RGB",
             int nPixels = 0):
    source{group},
    Xsize{sizeX},
    Ysize{sizeY},
    Xoffset{OffsetX},
    Yoffset{offsetY},
    format{pixel_format},
    nPix{nPixels}
    {
        if (format!="RGB") setPixelFormat(format);
            if (nPix==0) {
                nPix = Xsize*Ysize;
                nBytes = nPix*3;
            }
    }
    
    ofPixels& getPixels();
    
    void setPixelFormat(ofPixelFormat fmt) {pixelFormat = fmt;}
    void setPixelFormat(std::string fmt);
    
    int  getNumberOfPixels()    { return nPix;}
    int  getNumberOfBytes()     { return nBytes;}
    
    
    Group *         source;         // source group

    int             Xsize = 1;       // X length of the line
    int             Ysize = 0;       // how many lines to include
    int             Xoffset = 0;     // how many pixels to offset from (X)
    int             Yoffset = 0;     // how many lines to offset from
    
private:
    
    ofPixels        pixels;
    
    string          format{"RGB"}; // other choices: RGBA, BW, BWA
    ofPixelFormat   pixelFormat{OF_PIXELS_RGB};
    
    int             nPix;           // number of pixels
    int             nBytes;          // number of pixels
    
    friend class    ::Sink;
    
};
    
} // namespace Sinks

#endif /* LineBase_hpp */
