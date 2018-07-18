//
//  SourceFactory.cpp
//  Ellydeez
//
//  Created by Pascal Baltazar on 11/07/2018.
//

#include "SourceFactory.hpp"

void SourceFactory::update(){
    
}


void SourceFactory::setup(ofJson& c){
    
    cout << endl << "Building sources!" << endl << endl;
    
    cout << "Creating Pools:" << endl;
    
    // If there is no pool name in any of the sources, create a pool named default
    bool foundPools{false};
    for ( auto& src : c )
        if ( src.find("pool" ) != src.end()) foundPools = true;
    if ( ! foundPools ) { addPool( "default" ); cout << "No pool found in sources, adding default pool" << endl;}
    
    else {  // Create a pool for each new pool name
        for ( auto& src : c ){
            if ( src.count("pool") ){
                if ( ! pools.count( src["pool"] ) )
                { addPool( src[ "pool" ] ); cout << "Adding pool:" << src[ "pool" ] << endl;}
            }
        }
    }
    
    // Then create all Sources
    cout << endl << "Creating Sources:" << endl;
    for(auto src = c.begin(); src!= c.end(); ++src ){
        add( src.key(), src.value() );
    }
}



void SourceFactory::add( string srcName, ofJson& params ) {
    
    string name = srcName;
    if ( srcName.find( "syphon." ) == 0) {
        name.erase( 0, 7 );
        syphons.emplace( name, Sources::Syphon( params ) );
        sources.emplace( name, &syphons[ name ] );
        cout << endl << "Syphon: " << name << endl << setw(4) << params << endl;
        
    } else if ( srcName.find( "player." ) == 0) {
        name.erase( 0, 7 );
        players.emplace( name, Sources::Player( params ) );
        sources.emplace( name, &players[ name ] );
        cout << endl << "Player: " << name << endl << setw(4) << params << endl;
        
    } else {ofLogError("Config: ") << "unknown source type: " << name;}
    
}
