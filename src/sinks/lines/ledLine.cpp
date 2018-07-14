//
//  ledLine.cpp
//  Ellydeez
//
//  Created by Pascal Baltazar on 19/05/2018.
//

#include "ledLine.hpp"

namespace Sinks {

//--------------------------------------------------------------
// Send the whole thing to the LED line:
//
void LedLine::sendLine() {
    
    src->cropTo(pixelCrop, Xoffset, Yoffset, Xsize, Ysize);
    for (int i = 0; i < Xsize; ++i){
        for (int j = 0; j < Ysize; ++j){
            pixelCrop[(j*Xsize+i)*3+0] = pixelCrop[(j*Xsize+i)*3+0]*mapCol[bright]/255;
            pixelCrop[(j*Xsize+i)*3+1] = pixelCrop[(j*Xsize+i)*3+1]*mapCol[bright]/255;
            pixelCrop[(j*Xsize+i)*3+2] = pixelCrop[(j*Xsize+i)*3+2]*mapCol[bright]/255;
        }
    }
    
    sendPixelsAsBlobMessage(address, pixelCrop, nbPix*3);
    
}


//--------------------------------------------------------------
// Set APA102 Brightness for each LED line:
//
void LedLine::setBrightness(int brightness) {
    bright = uint8_t(brightness);
    sendValueAsIntMessage(address, mapBright[uint8_t(bright)]);
}

//--------------------------------------------------------------
// Set FastLED Brightness (aka dither) for each LED line:
//
/// TODO: that should be done for each serial output only, instead
//
void LedLine::setDither(int dither) {
    
    sendValueAsIntMessage("/b", dither);
    
}

} // namespace Sinks


