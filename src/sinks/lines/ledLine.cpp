//
//  ledLine.cpp
//  Ellydeez
//
//  Created by Pascal Baltazar on 19/05/2018.
//

#include "ledLine.hpp"

namespace Sinks {

void LedLine::update() {
    
    source->getPixels().cropTo(pixelCrop, Xoffset, Yoffset, Xsize, Ysize);
    
}

} // namespace Sinks


