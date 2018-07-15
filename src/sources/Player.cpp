//
//  Player.cpp
//  Ellydeez
//
//  Created by Pascal Baltazar on 13/07/2018.
//

#include "Player.hpp"

namespace Sources {
    
    void Player::setup(){
        
        player.setPixelFormat(pixelFormat);
        
        player.load(filePath);
        
        setLoopMode(loop);
        
        if(autoplay){
            player.play();
            player.setSpeed(speed);    
        }
        
        player.setPaused(paused);
        
    }
    
    void Player::setLoopMode(int mode){
        if      (mode == 1) {player.setLoopState(OF_LOOP_NORMAL);}
        else if (mode == 2) {player.setLoopState(OF_LOOP_PALINDROME);}
        else                {player.setLoopState(OF_LOOP_NONE);}
    }
    
} //namespace Sources

