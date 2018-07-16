//
//  outLine.hpp
//  Ellydeez
//
//  Created by Pascal Baltazar on 22/05/2018.
//

#ifndef outLine_hpp
#define outLine_hpp

#include <vector>
#include "Group.hpp"

class Sink;

namespace Sinks {
 
class OutLine {
    
public:
    
    OutLine(Group* group,
            int sizeX = 1, int sizeY = 0,
            int OffsetX = 0, int offsetY = 0,
            std::string pixel_format = "RGB",
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
    
    virtual void setup();
    virtual void udpate();
    virtual void draw();
    virtual void exit();
    
protected:
    
    virtual void send() = 0;
    
    void setPixelFormat(ofPixelFormat fmt) {pixelFormat = fmt;}
    void setPixelFormat(std::string fmt);
    
    
    Group *     source;      // source

    int             Xsize = 1;       // X length of the line
    int             Ysize = 0;       // how many lines to include
    int             Xoffset = 0;     // how many pixels to offset from (X)
    int             Yoffset = 0;     // how many lines to offset from
    int             nPix;           // number of pixels
    int             nBytes;          // number of pixels
    
    ofPixels        pixelCrop;
    
    std::string     format{"RGB"}; // other choices: RGBA, BW, BWA
    ofPixelFormat   pixelFormat{OF_PIXELS_RGB};
    
    
    friend class    ::Sink;
    
};
    
} // namespace Sinks

#endif /* outLine_hpp */
