//
//  ledLine.hpp
//  Ellydee
//
//  Created by Pascal Baltazar on 19/05/2018.
//

#ifndef ledLine_hpp
#define ledLine_hpp

#include "outLine.hpp"

class LedLine : public OutLine
{
public:
    
    void setBrightness(int brightness);
    void setDither(int dither);
    void sendLine();
    
};
//--------------------------------------------------------------

#endif /* ledLine_hpp */
