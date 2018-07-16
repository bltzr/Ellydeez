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
//#include "SinkPool.hpp"

using namespace std;

class SinkFactory;

class Sink {
    
public:
    
    Sink() = default;
    
    virtual ~Sink() = 0;
    
    virtual void setup() = 0;
    virtual void update() = 0;
    virtual void draw() = 0;
    virtual void exit() = 0 ;
    
protected:
    

    
private:
    
    friend class SinkFactory;
    
};

#endif /* SinkBase_hpp */
