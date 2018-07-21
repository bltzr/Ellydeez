//
//  Pool.cpp
//  Ellydeez
//
//  Created by Pascal Baltazar on 11/07/2018.
//

#include "Pool.hpp"

Pool::Pool(string name, ofJson& params):
poolName{name}
{
    width = ( params.count( "width" ) ) ? int(params[ "width" ]) : 1 ;
    height = ( params.count( "height" ) ) ? int(params[ "height" ]) : 0 ;
    setPixelFormat( format = ( params.count( "format" ) ) ? params[ "format" ] : "RGB" ) ;
}

uint8_t Pool::getPixelChannelValue(int Xpos, int Ypos, int channel){
    cout << ( (Xpos + Ypos * width ) * nChannels + channel ) << endl;
    return 255; // pixels [ ( Xpos + Ypos * width ) * nChannels + channel ] ;
}

int Pool::getPixelSummedValue(int Xpos, int Ypos){
    int res { 0 };
    int pos = ( Xpos + Ypos * width ) * nChannels;
    for (int i = 0; i < nChannels; ++i) {
        res += pixels [ pos  + i ];
    }
    return res;
}

void Pool::setPixelFormat(std::string fmt){
    if      ( fmt=="RGBA" )  {pixFormat=OF_PIXELS_RGBA;       nChannels = 4;}
    else if ( fmt==  "W"  )  {pixFormat=OF_PIXELS_GRAY;       nChannels = 1;}
    else if ( fmt== "WA"  )  {pixFormat=OF_PIXELS_GRAY_ALPHA; nChannels = 2;}
    else                     {pixFormat=OF_PIXELS_RGB; ;      nChannels = 3;}
    
}


void Pool::update() {
    if (activeSource) {
        activeSource -> update();
        pixels = activeSource -> getPixels();
    }
}


void Pool::addSource( string srcName, Source* src ) {
    poolSources[ srcName ] = src  ;
}

void Pool::removeSource( string srcName ) {
    poolSources.erase( srcName );
}

void Pool::moveSourceTo( string srcName, Pool* dstPool ){
    //if ( poolSources[ srcName ] ) {
      //  dstPool -> addSource ( srcName, poolSources[ srcName ] );
        //poolSources.erase( srcName );
    //}
}
