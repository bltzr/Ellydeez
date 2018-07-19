//
//  DMXLine.hpp
//  Ellydeez
//
//  Created by Pascal Baltazar on 22/05/2018.
//

#ifndef DMXLine_hpp
#define DMXLine_hpp

#include "LineBase.hpp"

namespace Sinks {
    
class SinkBase;

class DMXLine : public LineBase {
    
public:
    
    DMXLine():
    LineBase()
    {}
    
    DMXLine( ofJson& params ):
    LineBase{ params }
    {}
    
    ~DMXLine() = default;
    
    void setup()    {}
    void update();
    void draw()     {}
    void exit()     {}
    
};

} // namespace Sinks

#endif /* DMXLine_hpp */
