//
//  SourceFactory.cpp
//  Ellydeez
//
//  Created by Pascal Baltazar on 11/07/2018.
//

#include "SourceFactory.hpp"

void SourceFactory::update(){
    //cout << "------------------ updating sources" << endl;
    for (auto& pool : pools) pool.second.update();
}


void SourceFactory::setup(ofJson& c){
    
    // Create all Sources
    cout << endl << "Creating Sources:" << endl;
    for(auto src = c.begin(); src!= c.end(); ++src ){
        add( src.key(), src.value() );
    }

}

void SourceFactory::addPools( ofJson& c ){
    
    // Then create all Pools
    cout << endl << "Creating Pools:" << endl;
    for(auto pool = c.begin(); pool!= c.end(); ++pool ){
        auto poolName = pool.key() ; auto& poolParams = pool.value();
        cout << endl << poolName << endl << setw(4) << poolParams << endl;
        pools.emplace( poolName , Pool( poolParams ) );
        auto p = &pools[ poolName ];
        for (string srcN : poolParams[ "sources" ])
            if ( sources[ srcN ] ) {
                p -> addSource( srcN, sources[ srcN ] ) ;
                cout << "adding source " << srcN << " to pool " << poolName << endl;
            }
        p -> setActiveSource ( ( poolParams.count( "activeSource" ) ) ?
                  p -> poolSources[ poolParams[ "activeSource" ] ] : nullptr );
    }
    
}

void SourceFactory::add( string srcName, ofJson& params ) {
    
    string name = srcName;
    if ( srcName.find( "syphon." ) == 0) {
        name.erase( 0, 7 );
        syphons.emplace( name, Sources::Syphon( params ) );
        sources.emplace( srcName, &syphons[ name ] );
        cout << endl << "Syphon: " << name << endl << setw(4) << params << endl;
        syphons[ name ].setup();
        
    } else if ( srcName.find( "player." ) == 0) {
        name.erase( 0, 7 );
        players.emplace( name, Sources::Player( params ) );
        sources.emplace( srcName, &players[ name ] );
        cout << endl << "Player: " << name << endl << setw(4) << params << endl;
        players[ name ].setup();
        
    } else {ofLogError("Config: ") << "unknown source type: " << name;}
    
}

