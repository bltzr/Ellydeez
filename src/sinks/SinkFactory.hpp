//
//  SinkFactory.hpp
//  Ellydeez
//
//  Created by Pascal Baltazar on 13/07/2018.
//

#ifndef SinkFactory_hpp
#define SinkFactory_hpp

#include <stdio.h>
#include "sinks/OSC2APA102.hpp"

using namespace std;

class SinkFactory {
    
public:
    
    void setup( ofJson& config );
    
    void update();
    void draw();
    void exit();
    
    void addPools( map< string, Pool >& pools);
    
protected:
    
    void add( string sinkName, ofJson& params );
    
    void remove( const string& sinkName );
    void remove( Sink* );
    
private:
    
    map<string, Sinks::OSC2APA102>  osc2apa102s;
    
    map<string, Sink*>              sinks;
    
    map<string, Pool*>              pools;
    
};

#endif /* SinkFactory_hpp */
