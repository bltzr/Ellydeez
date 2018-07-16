//
//  PixelBase.hpp
//  Ellydeez
//
//  Created by Pascal Baltazar on 15/07/2018.
//

#ifndef PixelBase_hpp
#define PixelBase_hpp

#include <stdio.h>
#include "Group.hpp"

using namespace std;

class Sink;

namespace Sinks {
    
class PixelBase {
    
public:
    
    virtual void setup();
    virtual void udpate();
    virtual void draw();
    virtual void exit();
    
protected:
    
    PixelBase(Group* group,
              int positionX = 0,
              int positionY = 0,
              int pixelChannel = 0,
              string pixelFormat = "RGB"):
    source{group},
    Xpos{positionX},
    Ypos{positionY},
    pixPos{pixelChannel},
    format{pixelFormat}
    { if (format!="RGB") setPixelFormat(format); }
    
    uint8_t getValue();
    
    void setPixelFormat(ofPixelFormat fmt) {pixFormat = fmt;}
    void setPixelFormat(std::string fmt);
    
    Group *         source;      // source
    
    string          format{"RGB"}; // other choices: RGBA, BW, BWA
    ofPixelFormat   pixFormat{OF_PIXELS_RGB};
    
    int             Xpos = 0;
    int             Ypos = 0;
    int             pixPos = 0;
    
    int             pixMult{3};
    
    friend class    ::Sink;
    
};
    
} // namespace Sinks

#endif /* PixelBase_hpp */
