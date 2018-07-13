//
//  Syphon.hpp
//  Ellydeez
//
//  Created by Pascal Baltazar on 12/07/2018.
//

#ifndef Syphon_hpp
#define Syphon_hpp

#include <stdio.h>
#include "ofxSyphon.h"
#include "SourceBase.hpp"

namespace Sources {
    
class Syphon : public Source {
    
public:
    
    
    
private:
    
    ofxSyphonClient mClient ;
    ofFbo fbo ;
    
    std::string name;
    std::string app;
    
};

} //namespace Source

#endif /* Syphon_hpp */
