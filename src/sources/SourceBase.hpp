//
//  SourceBase.hpp
//  Ellydeez
//
//  Created by Pascal Baltazar on 11/07/2018.
//

#ifndef SourceBase_hpp
#define SourceBase_hpp

#include <stdio.h>
#include "ofMain.h"
#include "Group.hpp"

using namespace std;

class SourceFactory;
class Group;

class Source {
    
public:
    
    Source(Group* sourceGroup, string pixel_format = "RGB"):
    group{sourceGroup}
    {setPixelFormat(pixel_format);}
    
    virtual ~Source() = 0;
    
    virtual void setup() = 0;
    virtual void update() = 0;
    virtual void draw() = 0;
    virtual void exit() = 0;
    
protected:
    
    virtual ofPixels& getPixels()  = 0;
    
    void setPixelFormat(ofPixelFormat fmt) {pixelFormat = fmt;}
    void setPixelFormat(std::string fmt);
    
    Group*          group;
    int             Xsize{1};
    int             Ysize{0};
    
    string          format{"RGB"}; // other choices: RGBA, BW, BWA
    ofPixelFormat   pixelFormat{OF_PIXELS_RGB};
    
private:
    
    friend class    SourceFactory;
    
};
    
#endif /* SourceBase_hpp */
