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
    
    void setup();
    void update();
    void draw();
    void exit();
    
protected:
    
    ofPixels& getPixels();
    
private:
    
    ofxSyphonClient     mClient ;
    ofFbo               fbo ;
    ofPixels            pixels;
    
    int                 GLFormat{GL_RGB};
    bool                disableAlpha{1};
    
    std::string         name{""};
    std::string         app{"Simple Server"};
    
};

} //namespace Source

#endif /* Syphon_hpp */
