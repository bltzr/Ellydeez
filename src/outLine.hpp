//
//  outLine.hpp
//  Ellydeez
//
//  Created by Pascal Baltazar on 22/05/2018.
//

#ifndef outLine_hpp
#define outLine_hpp

#include "OSC2APA102.hpp"
#include "ofxOsc.h"

class OutLine
{
public:
    
    OutLine(OSC2APA102 * dev, ofPixels * src,
            int XOffset = 0, int Yoffset = 0,
            int Xsize = 0, int Ysize = 0):
    device{dev},
    source{src}
    {}
    
    OSC2APA102 * device; // serial device
    
    ofPixels * source;      // source
    string address;      // OSC address
    int nbPix;           // number of pixels
    int Xoffset = 0;
    int Yoffset = 0;     // how many lines to offset from
    int Xsize = 0;       // X length of the line
    int Ysize = 0;       // how many lines to include

    ofPixels pixelCrop;
    
    
    
    virtual void sendLine() = 0;
    
protected:
    void sendValueAsIntMessage(std::string addr, int v);
    void sendPixelsAsBlobMessage(std::string addr, ofPixels pix, int nBytes);
    
private:
    void sendOSCMessage( ofxOscMessage& message);

    
};

#endif /* outLine_hpp */
