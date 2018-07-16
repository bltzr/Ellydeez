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
#include "protocols/OSCDevice.hpp"

#include "APA102Line.hpp"
#include "DMXLine.hpp"
#include "brightPixel.hpp"

using namespace std;

namespace Sinks {
    
class OSC2APA102 : public SerialDevice, OSCDevice {
    
public:
    
    OSC2APA102(string addr):
        SerialDevice(addr),
        OSCDevice()
        {}
    
    OSC2APA102(int SN):
        SerialDevice(SN),
        OSCDevice()
        {}
    
    void setup();
    void update()
        { sendPacket( OSCBundle2ByteBuffer( fetchBundle() ) ); }
    
protected:
    
    Group *                     source;
    
    uint8_t                     brightness{255};
    
    map<string, APA102Line>     ledLines; // string is the OSC address
    map<string, DMXLine>        dmxLines; // string is the OSC address
    
    list<LineBase*>             allLines;
    
    int                         brightPixX {-1};
    int                         brightPixY {-1};
    int                         pixChannel  {0};
    
private:
    
    BrightPixel         brightPix{ source, brightPixX, brightPixY, pixChannel };
        
};

} // namespace Sinks

#endif /* OSC2APA102_hpp */
