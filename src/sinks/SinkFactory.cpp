//
//  SinkFactory.cpp
//  Ellydeez
//
//  Created by Pascal Baltazar on 13/07/2018.
//

#include "SinkFactory.hpp"

void SinkFactory::setup(ofJson& c){
    
    for(auto src = c.begin(); src!= c.end(); ++src ){
        cout << '\t' << "name: " << src.key() << endl;
        cout << '\t' << "content: " << endl << setw(4) << src.value() << endl;
    }
}


void SinkFactory::setup(){
    
}

void SinkFactory::update(){
    
}

