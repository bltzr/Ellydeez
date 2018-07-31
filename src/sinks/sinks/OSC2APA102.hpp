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

using namespace std;

namespace Sinks {
    
    class OSC2APA102 : public Sink, Devices::Serial, Protocols::OSC {
    
public:
    
    // Const/Destructors
    OSC2APA102() = default;
    OSC2APA102( ofJson& params );
    ~OSC2APA102() = default;
    
    // Copy constructors/assignments are disabled for now
    OSC2APA102( const OSC2APA102& other ) = delete;
    OSC2APA102& operator=( const OSC2APA102& other ) = delete;
        
    // Move constructors/assignments for including our class in a std::map 
    OSC2APA102( const OSC2APA102&& other ):
    ledLines{ move( other.ledLines ) },
    dmxLines{ move( other.dmxLines ) },
    allLines{ }
    {
        for (auto& l : ledLines ) allLines [ "APA102line."+l.first ] = &l.second;
        for (auto& l : dmxLines ) allLines [ l.first+"line" ]        = &l.second;
    }
    
    OSC2APA102& operator=( const OSC2APA102&& other ) {
        ledLines = move( other.ledLines ) ;
        dmxLines = move( other.dmxLines ) ;
        for (auto& l : ledLines ) allLines [ "APA102line."+l.first ] = &l.second;
        for (auto& l : dmxLines ) allLines [ l.first+"line" ]        = &l.second;
        return *this;
    }
        
    void setup( ofJson& params ) override;

    void update() override;
    void draw()   override  {}
    void exit()   override  {}
        
    void addPools( map< string, Pool* >& pools );
        
    void setPool( Pool* sourcePool ) override;
    void setPool( ofJson& params );
        
protected:
        
    void add( string lineName, ofJson& params );
    
    void remove( const string& lineName );
    void remove( Line* );
        
private:
             
    uint8_t                     brightness{255};
    
    map< string, Lines::APA102 >  ledLines; // string is the OSC address
    map< string, Lines::DMX >     dmxLines; // string is the OSC address
    
    map< string, Line* >          allLines; // string is the type + address
        
    map< string, Pool* >          pools;
    
    float                         brightXpos {-1};
    float                         brightYpos {-1};
    int                           brightChan  {0};
    
        
};

} // namespace Sinks

#endif /* OSC2APA102_hpp */
