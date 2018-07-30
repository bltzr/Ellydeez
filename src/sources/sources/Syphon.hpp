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
    
    Syphon() = default;
    Syphon( ofJson& params );
    
    ~Syphon() = default ;
    
    void setup( ofJson& params );
    
    void setup() override;
    void update() override;
    void draw() override {}
    void exit() override {}
    
    void draw (float x, float y, float w, float h) override;

    ofPixels& getPixels() override;
    
    float getWidth() override;
    float getHeight() override;
    
private:
    
    ofxSyphonClient     syphon;
    ofFbo               fbo;
    ofPixels            pixels;
    
    int                 GLFormat{GL_RGB};
    bool                disableAlpha{1};
    
    string              name{""};
    string              app{"Simple Server"};
    
};

} //namespace Source

#endif /* Syphon_hpp */
