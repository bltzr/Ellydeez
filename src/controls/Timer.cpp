//
//  Timer.cpp
//  Ellydeez
//
//  Created by Pascal Baltazar on 15/07/2018.
//

#include "Timer.hpp"

namespace Controls {
    
    void Timer::update(){
        ++timeCounter;
        if (timeCounter>100){
            Poco::Timestamp now;
            Poco::LocalDateTime nowLocal(now);
            std::string fmt = Poco::DateTimeFormat::SORTABLE_FORMAT;
            std::string timeNow = ofxTime::Utils::format(ofxTime::Utils::floor(nowLocal, Poco::Timespan::MINUTES), fmt);
            currentTime = (int(timeNow[11])-48)*10+int(timeNow[12])-48;
            bool previousTime = timeToPlay;
            timeToPlay = (currentTime > 10 && currentTime < 19);
            //if(timeToPlay!=previousTime){playing=timeToPlay; cout << "play: " << playing << endl; }
            timeCounter=0;
        }
    }
    
} // namespace Controls
    
