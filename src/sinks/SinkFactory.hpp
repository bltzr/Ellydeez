//
//  SinkFactory.hpp
//  Ellydeez
//
//  Created by Pascal Baltazar on 13/07/2018.
//

#ifndef SinkFactory_hpp
#define SinkFactory_hpp

#include <stdio.h>
#include "OSC2APA102.hpp"

using namespace std;

class SinkFactory {
    
public:
    
    void setup();
    void update();
    void draw();
    void exit();
    
protected:
    
    void add(string sinkName, ...);
    void remove(string sinkName);
    void remove(Sink*);
    
private:
    
    map<string, Sink*> sinks;
    // map<string, Group*>  groups; // ????
    
    list<Sinks::OSC2APA102> osc2apa102s;

    
};

#endif /* SinkFactory_hpp */
