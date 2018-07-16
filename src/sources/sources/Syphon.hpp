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

using namespace std;

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
    
    ofxSyphonClient     client ;
    ofFbo               fbo ;
    ofPixels            pixels;
    
    int                 GLFormat{GL_RGB};
    bool                disableAlpha{1};
    
    string              name{""};
    string              app{"Simple Server"};
    
};

} //namespace Source

#endif /* Syphon_hpp */
