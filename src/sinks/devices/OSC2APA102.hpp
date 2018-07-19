//
//  OSC2APA102.hpp
//  Ellydeez
//
//  Created by Pascal Baltazar on 19/05/2018.
//

#ifndef OSC2APA102_hpp
#define OSC2APA102_hpp

#include <list>
#include "outputs/SerialDevice.hpp"
#include "protocols/OSC.hpp"

#include "APA102Line.hpp"
#include "DMXLine.hpp"
#include "brightPixel.hpp"

using namespace std;

namespace Sinks {
    
    class OSC2APA102 : public SerialDevice, protocols::OSC {
    
public:
    
    OSC2APA102(string addr):
        SerialDevice(addr),
        OSC()
        {}
    
    OSC2APA102(int SN):
        SerialDevice(SN),
        OSC()
        {}
    
    void setup()    {}
    void update();
    void draw()     {}
    void exit()     {}
    
    
protected:
    
    Pool *                     source;
    
private:
    
    uint8_t                     brightness{255};
    
    map<string, APA102Line>     ledLines; // string is the OSC address
    map<string, DMXLine>        dmxLines; // string is the OSC address
    
    list<LineBase*>             allLines;
    
    int                         brightXpos {-1};
    int                         brightYpos {-1};
    int                         brightChan  {0};
        
};

} // namespace Sinks

#endif /* OSC2APA102_hpp */
