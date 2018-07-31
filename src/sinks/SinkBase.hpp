//
//  SinkBase.hpp
//  Ellydeez
//
//  Created by Pascal Baltazar on 13/07/2018.
//

#ifndef SinkBase_hpp
#define SinkBase_hpp

#include <stdio.h>
#include "ofMain.h"
#include "../sources/Pool.hpp"


using namespace std;

class SinkFactory;

class Sink {
    
public:

    
    virtual void setup( ofJson& params )    = 0;
    virtual void update()                   = 0;
    virtual void draw()                     = 0;
    virtual void exit()                     = 0;
    
    virtual void setPool( Pool* sourcePool ) { source = sourcePool;  }
    virtual void setPool( ofJson& params )   { source = pools[ params[ "source" ] ]; }
    
    virtual void addPools( map< string, Pool* >& pools );
    
    Pixel::Format getPixelFormat() { return m_format; }
    
protected:
    
    Sink() = default;
    
    virtual ~Sink() = default;
    
    void    setPixelFormat( Pixel::Format format );
    void    setPixelFormatFromString( string format );
    
    Pool*                   source;
    map< string, Pool* >    pools;
    
private:
    
    Pixel::Format             m_format{ Pixel::Format::NONE };
    ofPixelFormat           pixFormat{OF_PIXELS_RGB};
    
    friend class SinkFactory;
    
};

#endif /* SinkBase_hpp */
