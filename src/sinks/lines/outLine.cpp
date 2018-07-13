//
//  outLine.cpp
//  Ellydeez
//
//  Created by Pascal Baltazar on 22/05/2018.
//

#include "outLine.hpp"


//--------------------------------------------------------------
// OSC Message Management
//


void OutLine::sendValueAsIntMessage(std::string addr, int v)
{
    
    ofxOscMessage n;
    n.setAddress(addr);
    n.addIntArg(v);
    OSCmessages.push_back(n);
    
}

void OutLine::sendPixelsAsBlobMessage(std::string addr, ofPixels pix, int nBytes)
{
    
    ofBuffer imgAsBuffer;
    imgAsBuffer.clear();
    imgAsBuffer.append((const char*)pix.getData(),nBytes);
    
    ofxOscMessage m;
    m.setAddress(addr);
    m.addBlobArg(imgAsBuffer);
    OSCmessages.push_back(m);
    
}



