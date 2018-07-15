//
//  ledLine.hpp
//  Ellydeez
//
//  Created by Pascal Baltazar on 19/05/2018.
//

#ifndef ledLine_hpp
#define ledLine_hpp

#include "outLine.hpp"

namespace Sinks {

class LedLine : public OutLine {
    
public:
    
    void setup();
    void update();
    void draw();
    void exit();
    
private:
    
    

    
};

} // namespace Sinks

#endif /* ledLine_hpp */
