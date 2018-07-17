//
//  SourceFactory.cpp
//  Ellydeez
//
//  Created by Pascal Baltazar on 11/07/2018.
//

#include "SourceFactory.hpp"

void SourceFactory::setup(ofJson& config){
    
    // If there is no group names in the json config, create a group named default
    if (config.find("group") == config.end())
        { addGroup( "default" );}
    else {  // Create a group for each new group name
        for (auto src : config){
            if (src.count("group"))
                if (!groups.count( src["group"] ))
                    { addGroup( src["group"] );}
        }
    }
    
    // Then create all Sources
    
    
}

void SourceFactory::update(){

}

