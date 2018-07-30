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

using namespace std;

namespace Sources {
    
class Player : public Source {
    
public:
    
    Player() = default;
    Player( ofJson& params );
    
    ~Player() = default;
    
    void setup()    override;
    void update()   override;
    void draw()     override{}
    void exit()     override{}
    
    void draw  (float x, float y, float w, float h) override;
    
    ofPixels& getPixels() override { return player.getPixels(); }
    
    float getWidth() override;
    float getHeight() override;
    
    void setLoopMode(int mode);
    
private:
    
    ofVideoPlayer   player;
    
    string          filePath;
    bool            autoplay{0};
    int             loop{1};
    
    bool            loaded{0};
    
    float           speed{1.0};
    bool            paused{false};
    
};

} //namespace Source


#endif /* Player_hpp */
