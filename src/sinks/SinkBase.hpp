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
#include "Pool.hpp"


using namespace std;

class SinkFactory;

class Sink {
    
public:

    
    virtual void setup()    = 0;
    virtual void update()   = 0;
    virtual void draw()     = 0;
    virtual void exit()     = 0;
    
    virtual void setPool( Pool* sourcePool ) { source = sourcePool;  cout << "set base pool" << endl; }
    virtual void setPool( ofJson& params ) { source = pools[ params[ "source"] ]; cout << "setting pool from Base" << endl;}
    
    virtual void addPools(map< string, Pool* >& pools);
    
protected:
    
    Sink() = default;
    
    virtual ~Sink() = default;
    
    Pool*                   source;
    map<string, Pool*>      pools;
    
private:
    
    friend class SinkFactory;
    
};

#endif /* SinkBase_hpp */
