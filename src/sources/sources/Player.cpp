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
        autoplay = ( params.count( "autoplay" ) ) ? int(params[ "autoplay" ]) : true ;
        volume   = ( params.count( "volume" ) ) ? int(params[ "volume" ]) : 1. ;
    }
    
void Player::setup(){
    
    loaded = player.load( filePath );
    
    if ( loaded ) {
        width = player.getWidth();
        height = player.getHeight();
        
        setLoopMode(loop);
        
        if(autoplay){
            player.play();
            player.setSpeed(speed);
        } else { player.stop(); }
        
        player.setPaused(paused);
    }
}
    
void Player::update() {
    if ( loaded ) {
        // cout << "player " << filePath <<  " updating" << endl;
        player.setVolume( volume );
        player.setSpeed( speed );
        player.update();
    }
}

void Player::setLoopMode(int mode){
    if      (mode == 1) {player.setLoopState(OF_LOOP_NORMAL);}
    else if (mode == 2) {player.setLoopState(OF_LOOP_PALINDROME);}
    else                {player.setLoopState(OF_LOOP_NONE);}
}
    
void Player::draw (float x, float y, float w, float h) {
    player.draw( x, y, w, h);
}

float Player::getWidth() {
    return width = player.getWidth();
}

float Player::getHeight() {
    return height = player.getHeight();
}
    
} //namespace Sources

