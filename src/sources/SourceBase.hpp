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

using namespace std;

class SourceFactory;

class Source {
    
public:
    
    virtual void setup() = 0;
    virtual void update() = 0;
    virtual void draw() = 0;
    virtual void exit() = 0;
    
protected:
    
    Source()
    {}
    
    Source( ofJson& params )
    {}
    
    Source( const string& pixelFormat = "RGB" )
    {setPixelFormat(pixelFormat);}
    
    virtual ~Source() = default ;
    
    virtual ofPixels& getPixels()  = 0;
    
    void setPixelFormat(std::string fmt);
    
    
    int             width{1};
    int             height{0};
    
    string          format{"RGB"}; // other choices: RGBA, G, GA
    ofPixelFormat   pixFormat{OF_PIXELS_RGB};
    
private:
    
    friend class    SourceFactory;
    
};
    
#endif /* SourceBase_hpp */
