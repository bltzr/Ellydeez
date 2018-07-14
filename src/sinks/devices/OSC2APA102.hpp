//
//  OSC2APA102.hpp
//  Ellydeez
//
//  Created by Pascal Baltazar on 19/05/2018.
//

#ifndef OSC2APA102_hpp
#define OSC2APA102_hpp

#include <list>
#include "OSCDevice.hpp"
#include "ledLine.hpp"
#include "DMXLine.hpp"


namespace Sinks {
    
    class OSC2APA102 : public OSCDevice {
        
    public:
        
        OSC2APA102(std::string addr):
            OSCDevice(addr)
            {}
        
        OSC2APA102(int SN):
            OSCDevice(SN)
            {}
        
    protected:
        
        uint8_t brightness{255};
        
        std::list<LedLine> ledLines;
        std::list<DMXLine> dmxLines;
        
        std::list<OutLine*> outLines;
        
        int brightPixX{-1};
        int brightPixY{-1};
        
};

} // namespace Sinks

#endif /* OSC2APA102_hpp */
