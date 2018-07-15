//
//  OSCin.cpp
//  Ellydeez
//
//  Created by Pascal Baltazar on 15/07/2018.
//

#include "OSCin.hpp"

/*
 
 // Treat incoming OSC Messages:
 
 while(receiver.hasWaitingMessages()){
 // get the next message
 ofxOscMessage m;
 receiver.getNextMessage(m);

 if(m.getAddress() == "/b"){
 ofLog() << "b" << m.getArgAsInt32(0);
 for (int i=0; i<NUM_LEDLINES; i++){
 ledLine[i].setBrightness(m.getArgAsInt32(0));
 }
 }
 else if(m.getAddress() == "/d"){
 for (int i=0; i<NUM_LEDLINES; i++){
 ledLine[i].setDither(m.getArgAsInt32(0));
 }
 ofLog() << "d" << m.getArgAsInt32(0);
 }
 else if(m.getAddress() == "/play"){
     ofLog() << "play" << m.getArgAsInt32(0);
     if(m.getArgAsBool(0)){trame.play(); trame.setLoopState(OF_LOOP_NORMAL); playing = 1;}
     else if(!m.getArgAsBool(0)){trame.stop(); playing = 0;}
 }
else if(m.getAddress() == "/pause"){
    ofLog() << "pause" << m.getArgAsInt32(0);
    if(m.getArgAsBool(0)){trame.setPaused(1);}
    
    else if(!m.getArgAsBool(0)){trame.setPaused(0);}
}
else if(m.getAddress() == "/draw"){
    ofLog() << "draw" << m.getArgAsInt32(0);
    drawing = m.getArgAsBool(0);
}
else if(m.getAddress() == "/position"){
    ofLog() << "position" << m.getArgAsFloat(0);
    trame.setPosition(m.getArgAsFloat(0));
}
else if(m.getAddress() == "/speed"){
    ofLog() << "speed" << m.getArgAsFloat(0);
    trame.setSpeed(m.getArgAsFloat(0));
}
}
 
 */
