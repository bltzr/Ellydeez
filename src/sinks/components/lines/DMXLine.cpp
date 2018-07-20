//
//  DMXLine.cpp
//  Ellydeez
//
//  Created by Pascal Baltazar on 22/05/2018.
//

#include "DMXLine.hpp"

namespace Sinks {

    void DMXLine::update() {
        
        fetchPixelsfromSource();
        
    }

} // namespace Sinks
