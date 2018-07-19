//
//  OSC.hpp
//  Ellydeez
//
//  Created by Pascal Baltazar on 14/07/2018.
//

#ifndef OSCDevice_hpp
#define OSCDevice_hpp

#include <stdio.h>
#include "ofMain.h"
#include "ofxOsc.h"

#include "ofxIO.h"

using namespace std;

namespace Sinks {
namespace protocols {
    
class OSC {
   
public:
    
    OSC()     = default ;
    ~OSC()    = default ;
      
protected:
    
    // For clients:
    osc::OutboundPacketStream fetchBundle() ;
    
    // For components:
    void sendValueAsIntMessage  ( string addr, int value );
    void sendPixelsAsBlobMessage( string addr, const ofPixels& pix, int nBytes );

private:
    
    void appendOSCMessage(osc::OutboundPacketStream& packet,
                          ofxOscMessage& message);
    
    vector<ofxOscMessage> OSCmessages;
    
};

    
////////////// Helper Functions: //////////////

///@brief: Encode an OSC Bundle to a Byte Buffer with SLIP encoding
ofx::IO::ByteBuffer OSCBundle2ByteBuffer ( const osc::OutboundPacketStream& packet );
    
} // namespace   protocols
} //namespace Sinks
    

#endif /* OSCDevice_hpp */
