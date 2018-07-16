//
//  APA102Line.cpp
//  Ellydeez
//
//  Created by Pascal Baltazar on 15/07/2018.
//

#include "APA102Line.hpp"

namespace Sinks {

void APA102Line::update() {
    
    bright = brightPix.getValue();
    
    ofPixels& pix = getPixels();

    for (int i = 0; i < Xsize; ++i){
        for (int j = 0; j < Ysize; ++j){
            pix[(j*Xsize+i)*3+0] = pix[(j*Xsize+i)*3+0]*mapCol[bright]/255;
            pix[(j*Xsize+i)*3+1] = pix[(j*Xsize+i)*3+1]*mapCol[bright]/255;
            pix[(j*Xsize+i)*3+2] = pix[(j*Xsize+i)*3+2]*mapCol[bright]/255;
        }
    }

    sendPixelsAsBlobMessage(address, pixelCrop, nbPix*3);

}


//--------------------------------------------------------------
// Set APA102 Brightness for each LED line:
//
void APA102Line::setBrightness(int brightness) {
    bright = uint8_t(brightness);
    sendValueAsIntMessage(address, mapBright[uint8_t(bright)]);
}

//--------------------------------------------------------------
// Set FastLED Brightness (aka dither) for each LED line:
//
/// TODO: that should be done for each serial output only, instead
//
void APA102Line::setDither(int dither) {
    
    sendValueAsIntMessage("/b", dither);
    
}
    
} // namespace Sinks
