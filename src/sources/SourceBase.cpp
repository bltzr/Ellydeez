//
//  SourceBase.cpp
//  Ellydeez
//
//  Created by Pascal Baltazar on 11/07/2018.
//

#include "SourceBase.hpp"

void Source::setPixelFormat(string fmt){
    if (fmt=="RGBA")     pixFormat=OF_PIXELS_RGBA;
    else if (fmt=="BW")  pixFormat=OF_PIXELS_GRAY;
    else if (fmt=="BWA") pixFormat=OF_PIXELS_GRAY_ALPHA;
    else                 pixFormat=OF_PIXELS_RGB;
    
}
