//
//  Player.cpp
//  Ellydeez
//
//  Created by Pascal Baltazar on 13/07/2018.
//

#include "Player.hpp"

namespace Sources {
    
    Player::Player( ofJson& params ):
    Source( )
    {
        filePath = ( params.count( "filePath" ) ) ? params[ "filePath" ] : "" ;
        width = ( params.count( "width" ) ) ? int(params[ "width" ]) : 1 ;
        height = ( params.count( "height" ) ) ? int(params[ "height" ]) : 0 ;
        format = ( params.count( "format" ) ) ? params[ "format" ] : "RGB" ;
    }
    
void Player::setup(){
    
    player.setPixelFormat(pixFormat);
    
    player.load(filePath);
    width = player.getWidth();
    height = player.getHeight();
    
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

