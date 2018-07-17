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
    
    virtual void setup() = 0;
    virtual void update() = 0;
    virtual void draw() = 0;
    virtual void exit() = 0;
    
protected:
    
    Source(Group* sourceGroup,
           string pixelFormat = "RGB"):
        group{sourceGroup}
        {setPixelFormat(pixelFormat);}
    
    virtual ~Source() = 0;
    
    virtual ofPixels& getPixels()  = 0;
    
    void setPixelFormat(std::string fmt);
    
    Group*          group;
    
    int             Xsize{1};
    int             Ysize{0};
    
    string          format{"RGB"}; // other choices: RGBA, BW, BWA
    ofPixelFormat   pixFormat{OF_PIXELS_RGB};
    
private:
    
    friend class    SourceFactory;
    
};
    
#endif /* SourceBase_hpp */
