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
    
    void setup()    override {}
    void update()  override {
        cout << "actually updating DMXLine" << endl;
        //fetchPixelsfromSource();
    }
    void draw()    override  {}
    void exit()    override  {}
    
};

} // namespace Lines
} // namespace Sinks

#endif /* DMXLine_hpp */
