//
//  Player.cpp
//  Ellydeez
//
//  Created by Pascal Baltazar on 13/07/2018.
//

#include "Player.hpp"

namespace Sources {
    
    void Player::setup(){
        
        if (format=="RGBA") pixelFormat=OF_PIXELS_RGBA;
        else if (format=="BW") pixelFormat=OF_PIXELS_GRAY;
        else if (format=="BWA") pixelFormat=OF_PIXELS_GRAY_ALPHA;
        else pixelFormat=OF_PIXELS_RGB;
            
        player.setPixelFormat(pixelFormat);
        
        player.load(filePath);
        
        if (loop == 1){player.setLoopState((OF_LOOP_NORMAL));}
        else if (loop == 2){player.setLoopState((OF_LOOP_PALINDROME));}
        else {player.setLoopState(OF_LOOP_NONE);}
        
        if(autoplay){
            player.play();
            player.setSpeed(speed);    
        }
        
        player.setPaused(paused);
        
    }
    
} //namespace Sources


/*
 
 ofVideoPlayer player;
 
 ofPath path;
 bool autoplay{0};
 int loop{1};
 ofPixelFormat pixelFormat{OF_PIXELS_RGB};
 
 float speed{1.0};
 bool paused{0};
 


*/
