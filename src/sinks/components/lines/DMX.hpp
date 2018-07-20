//
//  DMX.hpp
//  Ellydeez
//
//  Created by Pascal Baltazar on 22/05/2018.
//

#ifndef DMXLine_hpp
#define DMXLine_hpp

#include "../LineBase.hpp"

namespace Sinks {
namespace Lines {

    class DMX : public Line {
    
public:
    
    DMX():
    Line()
    {}
    
    DMX( ofJson& params ):
    Line( params )
    {}
    
    ~DMX() = default;
    
    void setup()    {}
    void update()  { fetchPixelsfromSource(); }
    void draw()     {}
    void exit()     {}
    
};

} // namespace Lines
} // namespace Sinks

#endif /* DMXLine_hpp */
