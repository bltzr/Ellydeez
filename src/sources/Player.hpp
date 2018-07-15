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
        
        void setup();
        
    private:
        
        ofVideoPlayer   player;
        
        std::string     filePath;
        bool            autoplay{0};
        int             loop{1};
        std::string     format{"RGB"}; // other choices: RGBA, BW, BWA
        ofPixelFormat   pixelFormat{OF_PIXELS_RGB};
        
        float           speed{1.0};
        bool            paused{false};
        
    };
    
} //namespace Source


#endif /* Player_hpp */
