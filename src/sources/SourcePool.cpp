//
//  SourcePool.cpp
//  Ellydeez
//
//  Created by Pascal Baltazar on 11/07/2018.
//

#include "SourcePool.hpp"

void SourcePool::setup(ofJson& config){
    
    // Find if there is one or more group names in the json config
    if (false) {
        ;
    }
    // if not, then create a group named default
    else groups.emplace( "default" , Group("default") );
    
    // Then create all Sources
    
    
}
