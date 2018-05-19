//
//  ledLine.hpp
//  ledMapper
//
//  Created by Pascal Baltazar on 19/05/2018.
//

#ifndef ledLine_hpp
#define ledLine_hpp

#include "OSC2APA102.hpp"

#include "ofxOsc.h"



class LedLine
{
public:
    ofPixels * src;  // source
    string address;  // OSC address
    int nbPix;       // number of pixels
    int Xoffset;
    int Yoffset;     // how many lines to offset from
    int Xsize;       // X length of the line
    int Ysize;       // how many lines to include
    OSC2APA102 * dev;
    ofPixels pixelCrop;
    
    void setBrightness(int brightness);
    void setDither(int dither);
    void sendLine();
    
private:
    uint8_t brightness;
    uint8_t dither;
    void appendMessage( ofxOscMessage& message, osc::OutboundPacketStream& p );
    
};
//--------------------------------------------------------------

#endif /* ledLine_hpp */
