//
//  BrightPixel.hpp
//  Ellydeez
//
//  Created by Pascal Baltazar on 16/07/2018.
//

#ifndef BrightPixel_hpp
#define BrightPixel_hpp

#include <stdio.h>

#include "PixelBase.hpp"

namespace Sinks {
    
    
    class BrightPixel : public PixelBase {
        
    public:
        
        BrightPixel(Group* group,
                    int positionX = 0,
                    int positionY = 0,
                    int pixelChannel = 0,
                    string pixelFormat = "RGB"):
        PixelBase{ group, positionX, positionY, pixelChannel, pixelFormat}
        {}
        
    protected:
        
        
    };
    
} // namespace Sinks

#endif /* BrightPixel_hpp */
