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

class SinkPool;

class Sink {
    
public:
    
    void init();
    void update();
    void draw();
    void exit();
    
protected:
    

    
private:
    
    friend class SinkPool;
    
};

#endif /* SinkBase_hpp */
