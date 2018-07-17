//
//  SourceFactory.cpp
//  Ellydeez
//
//  Created by Pascal Baltazar on 11/07/2018.
//

#include "SourceFactory.hpp"

void SourceFactory::setup(ofJson& c){
    
    cout << endl << "Building sources!" << endl << endl;
    
    cout << "Creating Groups:" << endl;
    
    // If there is no group names in any of the sources, create a group named default
    bool foundGroups{false};
    for (auto& src : c)
        if (src.find("group") != src.end()) foundGroups = true;
    if ( ! foundGroups ) { addGroup( "default" ); cout << "No group found in sources, adding default group" << endl;}
    
    else {  // Create a group for each new group name
        for (auto& src : c){
            if (src.count("group")){
                foundGroups = true;
                if (!groups.count( src["group"] ))
                { addGroup( src["group"] ); cout << "Adding group:" << src["group"] << endl;}
            }
        }
    }
    
    // Then create all Sources
    cout << endl << "Creating Sources:" << endl;
    for(auto src = c.begin(); src!= c.end(); ++src ){
        cout << "name: " << src.key() << endl;
        cout << "content: " << endl << setw(4) << src.value() << endl;
    }
}

void SourceFactory::update(){

}

