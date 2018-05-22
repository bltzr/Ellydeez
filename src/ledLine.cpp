//
//  ledLine.cpp
//  Ellydee
//
//  Created by Pascal Baltazar on 19/05/2018.
//

#include "ledLine.hpp"

//--------------------------------------------------------------
// Send the whole thing to the LED line:
//
void LedLine::sendLine() {
    
    src->cropTo(pixelCrop, Xoffset, Yoffset, Xsize, Ysize);
    
    sendPixelsAsBlobMessage(address, pixelCrop, nbPix*3);
    
}


//--------------------------------------------------------------
// Set APA102 Brightness for each LED line:
//
void LedLine::setBrightness(int brightness) {

    sendValueAsIntMessage(address, brightness);
    
}

//--------------------------------------------------------------
// Set FastLED Brightness (aka dither) for each LED line:
//
/// TODO: that should be done for each serial output only, instead
//
void LedLine::setDither(int dither) {
    
    sendValueAsIntMessage("/b", dither);
    
}




