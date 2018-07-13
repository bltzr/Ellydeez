//
//  OSC2APA102.hpp
//  Ellydee
//
//  Created by Pascal Baltazar on 19/05/2018.
//

#ifndef OSC2APA102_hpp
#define OSC2APA102_hpp

#include <list>
#include "ofxSerial.h"
#include "Serial.hpp"
#include "ledLine.hpp"
#include "DMXLine.hpp"


namespace Sinks {
    
    class OSC2APA102 : public Sinks::Serial {
        
    public:
        
        OSC2APA102(std::string addr):
            Serial(addr)
            {}
        
        OSC2APA102(int SN):
            Serial(SN)
            {}
        
    protected:
        
        uint8_t brightness{255};
        
        std::list<LedLine> ledLines;
        std::list<DMXLine> dmxLines;
        
        std::list<OutLine*> outLines;
        
        
        int brightPixX{-1};
        int brightPixY{-1};
                
        void sendOSCBundle();
        
        void appendOSCMessage(osc::OutboundPacketStream& packet,
                              ofxOscMessage& message);
        
        friend class OutLine;
        
};

} // namespace Sinks

#endif /* OSC2APA102_hpp */
