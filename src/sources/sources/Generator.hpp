//
//  Generator.hpp
//  Ellydeez
//
//  Created by Pascal Baltazar on 13/07/2018.
//

#ifndef Generator_hpp
#define Generator_hpp

#include <stdio.h>
#include "SourceBase.hpp"

using namespace std;

namespace Sources {
    
class Generator : public Source {
    
public:
    
    Generator():
    Source()
    {}
    
    ~Generator() = default;
    
    void setup()    override;
    void update()   override;
    void draw()     override{}
    void exit()     override{}
    
    void draw( float x, float y, float w, float h ) override;
    
    ofPixels& getPixels() override;
    
    float getWidth() override;
    float getHeight() override;
    
private:
    
    
    
};
    
} //namespace Source

#endif /* Generator_hpp */
