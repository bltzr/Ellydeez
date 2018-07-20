//
//  OSC2APA102.hpp
//  Ellydeez
//
//  Created by Pascal Baltazar on 19/05/2018.
//

#ifndef OSC2APA102_hpp
#define OSC2APA102_hpp

#include <list>
#include "../devices/Serial.hpp"
#include "../protocols/OSC.hpp"

#include "../components/lines/APA102.hpp"
#include "../components/lines/DMX.hpp"
#include "brightPixel.hpp"

using namespace std;

namespace Sinks {
    
    class OSC2APA102 : public Devices::Serial, Protocols::OSC {
    
public:
    
        OSC2APA102() = default;
        
        OSC2APA102( ofJson& params ):
        Serial(),
        OSC()
        { setup ( params ); }
        
        OSC2APA102( string addr, ofJson& params ):
        Serial( addr ),
        OSC()
        { setup ( params ); }
        
        OSC2APA102( int SN, ofJson& params ):
        Serial( SN ),
        OSC()
        { setup ( params ); }
    
        ~OSC2APA102() = default;
    
    void setup( ofJson& params );

    void update() override;
    void draw()   override  {}
    void exit()   override  {}
    
    
protected:
    
    Pool *                     source;
        
    void add( string lineName, ofJson& params );
    
    void remove( const string& lineName );
    void remove( Line* );
    
private:
    
    uint8_t                     brightness{255};
    
    map<string, Lines::APA102>     ledLines; // string is the OSC address
    map<string, Lines::DMX>        dmxLines; // string is the OSC address
    
    map<string, Line*>             allLines; // string is the type + address
    
    int                         brightXpos {-1};
    int                         brightYpos {-1};
    int                         brightChan  {0};
        
};

} // namespace Sinks

#endif /* OSC2APA102_hpp */
