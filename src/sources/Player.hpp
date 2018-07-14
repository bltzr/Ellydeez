//
//  Player.hpp
//  Ellydeez
//
//  Created by Pascal Baltazar on 13/07/2018.
//

#ifndef Player_hpp
#define Player_hpp

#include <stdio.h>
#include "SourceBase.hpp"

namespace Sources {
    
    class Player : public Source {
        
    public:
        
        
        
    private:
        
        ofVideoPlayer player;
        
        ofPath path;
        bool autoplay{0};
        bool loop{1};
        ofPixelFormat pixelFormat{OF_PIXELS_RGB};
        
        float speed{1};
        bool paused{0};
        
    };
    
} //namespace Source


#endif /* Player_hpp */
