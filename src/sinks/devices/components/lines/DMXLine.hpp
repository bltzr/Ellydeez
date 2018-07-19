//
//  DMXLine.hpp
//  Ellydee
//
//  Created by Pascal Baltazar on 22/05/2018.
//

#ifndef DMXLine_hpp
#define DMXLine_hpp

#include "LineBase.hpp"

namespace Sinks {
    
class SinkBase;

class DMXLine : public LineBase {
    
public:
    
    DMXLine(Pool* pool,
            int sizeX = 1,   int sizeY = 0,
            int OffsetX = 0, int offsetY = 0,
            string pixelFormat = "W",
            int nPixels = 0):
    LineBase{pool, sizeX, sizeY, OffsetX, offsetY, pixelFormat, nPixels}
    {}
    
};

} // namespace Sinks

#endif /* DMXLine_hpp */
