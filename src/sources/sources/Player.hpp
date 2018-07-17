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
    
    Player(Group* sourceGroup,
           string pixelFormat = "RGB"):
    Source(sourceGroup, pixelFormat)
    {}
    
    ~Player() = default;
    
    void setup();
    void update() { player.update(); }
    void draw(){}
    void exit(){}
    
protected:
    
    ofPixels& getPixels() { return player.getPixels(); }
    
    void setLoopMode(int mode);
    
private:
    
    ofVideoPlayer   player;
    
    string          filePath;
    bool            autoplay{0};
    int             loop{1};
    
    float           speed{1.0};
    bool            paused{false};
    
};

} //namespace Source


#endif /* Player_hpp */
