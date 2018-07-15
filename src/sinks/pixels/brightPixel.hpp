//
//  brightPixel.hpp
//  Ellydeez
//
//  Created by Pascal Baltazar on 15/07/2018.
//

#ifndef brightPixel_hpp
#define brightPixel_hpp

#include <stdio.h>
#include "Group.hpp"

class Sink;

namespace Sinks {
    
    class BrightPixel {
        
    public:
        
        BrightPixel(Group* group,
                    int PositionX = 0,
                    int PositionY = 0):
        source{group},
        Xpos{PositionX},
        Ypos{PositionY}
        {}
        
        virtual void setup();
        virtual void udpate();
        virtual void draw();
        virtual void exit();
        
    protected:
        
        virtual void send();
        
        int brightness{255};
        
        Group * source;      // source
        std::string address; // OSC address
        int Xpos = 0;
        int Ypos = 0;
        
        friend class ::Sink;
        
    };
    
} // namespace Sinks

#endif /* brightPixel_hpp */
