//
//  LineBase.hpp
//  Ellydeez
//
//  Created by Pascal Baltazar on 22/05/2018.
//

#ifndef LineBase_hpp
#define LineBase_hpp

#include <vector>
#include "ofMain.h"
#include "../../sources/Pool.hpp"

using namespace std;

//class Sink;

namespace Sinks {
 
class Line {
    
public:
    
    virtual void setup() {}
    virtual void update() { cout << "updating LineBase" << endl; }
    virtual void draw() {}
    virtual void exit() {}
    
    const ofPixels& getPixels();
    
    Pixel::Format  getPixelFormat() { return m_format; }
    
    float     getWidth()      { return width;}
    float     getHeight()     { return height;}
    float     getXpos()      { return Xpos;}
    float     getYpos()     { return Ypos;}
    
    int     getNumChannels() { return nChannels; }
    
    int     getNumberOfPixels()    { return nPix;}
    int     getNumberOfBytes()     { return nBytes;}
    
    virtual void    setPool  ( Pool* sourcePool ) { source = sourcePool; }
    Pool* getPool() {return source;}
    
protected:
    
    Line()
    {}
    
    Line( ofJson& params );
    
    virtual ~Line() = default;
    
    void    setPixelFormat( Pixel::Format format );
    void    setPixelFormatFromString( string format );
    
    void    fetchPixelsfromSource();
    
    Pool *          source;         // source pool

    float             width = 1;       // X length of the line
    float             height = 0;       // how many lines to include
    float             Xpos = 0;     // how many pixels to offset from (X)
    float             Ypos = 0;     // how many lines to offset from
    
    ofPixels        pixels;         
    
private:
    
    Pixel::Format   m_format{ Pixel::Format::RGB };
    ofPixelFormat   pixFormat{OF_PIXELS_RGB};
    
    int             nChannels{3};
    int             nPix{0};           // number of pixels
    int             nBytes{0};          // number of pixels
    
    //friend class    ::Sink;
    
};
    
} // namespace Sinks

#endif /* LineBase_hpp */
