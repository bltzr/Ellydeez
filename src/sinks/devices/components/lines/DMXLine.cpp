//
//  DMXLine.cpp
//  Ellydee
//
//  Created by Pascal Baltazar on 22/05/2018.
//

#include "DMXLine.hpp"

namespace Sinks {


//--------------------------------------------------------------
// Send the whole thing to the DMX line:
//
void DMXLine::send() {
    
    source->getPixels().cropTo(pixelCrop, Xoffset, Yoffset, Xsize, Ysize);
    
    sendPixelsAsBlobMessage(address, pixelCrop, nPix);
    
}

} // namespace Sinks
