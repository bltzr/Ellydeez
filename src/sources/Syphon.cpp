//
//  Syphon.cpp
//  Ellydeez
//
//  Created by Pascal Baltazar on 12/07/2018.
//

#include "Syphon.hpp"

namespace Sources {
    
    void Syphon::setup(){

        mClient.setup();
        mClient.set( name , app );
        
    }

} // namespace Sources
