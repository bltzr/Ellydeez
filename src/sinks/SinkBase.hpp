//
//  SinkBase.hpp
//  Ellydeez
//
//  Created by Pascal Baltazar on 13/07/2018.
//

#ifndef SinkBase_hpp
#define SinkBase_hpp

#include <stdio.h>
#include "ofMain.h"

using namespace std;

class SinkFactory;

class Sink {
    
public:

    
    virtual void setup()    = 0;
    virtual void update()   = 0;
    virtual void draw()     = 0;
    virtual void exit()     = 0;
    
    
    
protected:
    
    Sink() = default;
    
    virtual ~Sink() = default;
    
    
    
private:
    
    friend class SinkFactory;
    
};

#endif /* SinkBase_hpp */
