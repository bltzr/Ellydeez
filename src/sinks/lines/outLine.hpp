//
//  outLine.hpp
//  Ellydeez
//
//  Created by Pascal Baltazar on 22/05/2018.
//

#ifndef outLine_hpp
#define outLine_hpp

#include <vector>
#include "Group.hpp"

class Sink;

namespace Sinks {
 
    class OutLine {
        
    public:
        
        OutLine(Group* group,
                int sizeX = 1, int sizeY = 0,
                int OffsetX = 0, int offsetY = 0,
                int nPixels = 0):
        source{group},
        Xsize{sizeX},
        Ysize{sizeY},
        Xoffset{OffsetX},
        Yoffset{offsetY},
        nbPix{nPixels}
        { if (nbPix==0) nbPix = Xsize*Ysize; }

        virtual void sendLine() = 0;
        
    protected:
        
        Group * source;      // source
        std::string address;      // OSC address
        int Xsize = 1;       // X length of the line
        int Ysize = 0;       // how many lines to include
        int Xoffset = 0;     // how many pixels to offset from (X)
        int Yoffset = 0;     // how many lines to offset from
        int nbPix;           // number of pixels
        
        ofPixels pixelCrop;
        
        friend class ::Sink;
        
    };
    
} // namespace Sinks

#endif /* outLine_hpp */
