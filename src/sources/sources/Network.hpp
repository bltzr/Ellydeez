//
//  Network.hpp
//  Ellydeez
//
//  Created by Pascal Baltazar on 13/07/2018.
//

#ifndef Network_hpp
#define Network_hpp

#include <stdio.h>
#include "SourceBase.hpp"

namespace Sources {

class Network : public Source {
    
public:
    
    Network( ):
    Source( )
    {}
    
    ~Network() = default;
    
    void setup()    override;
    void update()   override;
    void draw()     override{}
    void exit()     override{}
    
    void draw  (float x, float y, float w, float h) override;
    
    ofPixels& getPixels() override;
    
    float getWidth() override;
    float getHeight() override;
    
private:
    
    int port;
    
    
};
    
} //namespace Source

#endif /* Network_hpp */
