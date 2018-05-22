//
//  DMXLine.cpp
//  Ellydee
//
//  Created by Pascal Baltazar on 22/05/2018.
//

#include "DMXLine.hpp"

//--------------------------------------------------------------
// Send the whole thing to the DMX line:
//
void DMXLine::sendLine() {
    
    src->cropTo(pixelCrop, Xoffset, Yoffset, Xsize, Ysize);
    
    sendPixelsAsBlobMessage(address, pixelCrop, nbPix);
    
}
