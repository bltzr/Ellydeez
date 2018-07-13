//
//  outLine.hpp
//  Ellydeez
//
//  Created by Pascal Baltazar on 22/05/2018.
//

#ifndef outLine_hpp
#define outLine_hpp


#include <vector>
#include "ofxOsc.h"
#include "ofMain.h"
#include "OSC2APA102.hpp"

//class Sinks::OSC2APA102;

class OutLine
{
public:
    
    OutLine(//OSC2APA102 * dev, ofPixels * src,
            int Xsize = 1, int Ysize = 0,
            int XOffset = 0, int Yoffset = 0
            )
    //device{dev},
    //source{src}
    {}
    
    //OSC2APA102 * device; // serial device
    
    ofPixels * source;      // source
    std::string address;      // OSC address
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
    
    std::vector<ofxOscMessage> OSCmessages;
    
private:
    void sendOSCMessage( ofxOscMessage& message);
    
    friend class Sinks::OSC2APA102;

    
};

#endif /* outLine_hpp */
