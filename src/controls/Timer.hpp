//
//  Timer.hpp
//  Ellydeez
//
//  Created by Pascal Baltazar on 15/07/2018.
//

#ifndef Timer_hpp
#define Timer_hpp

#include <stdio.h>
#include "ofxTime.h"

namespace Controls {
    
class Timer {
    
public:
    
    void setup();
    void update();
    void draw();
    
private:
    
    int currentTime{0};
    int timeToPlay{0};
    int timeCounter{0};
    
};
}

#endif /* Timer_hpp */
