//
//  SinkFactory.cpp
//  Ellydeez
//
//  Created by Pascal Baltazar on 13/07/2018.
//

#include "SinkFactory.hpp"

void SinkFactory::update(){
    cout << "------------------ updating sinks" <<endl;
    for (auto& sink : sinks) sink.second->update();
}



void SinkFactory::setup(ofJson& c){
    
    // Create all Sinks
    cout << endl << "Creating Sinks:" << endl;
    for(auto sink = c.begin(); sink!= c.end(); ++sink ){
        add( sink.key(), sink.value() );
    }
    
}


void SinkFactory::add( string sinkName, ofJson& params ) {
    
    string name = sinkName;
    if ( sinkName.find( "osc2apa102." ) == 0) {
        name.erase( 0, 11 );
        osc2apa102s.emplace( name, Sinks::OSC2APA102( params ) );
        sinks.emplace( sinkName, &osc2apa102s[ name ] );
        cout << endl << "OSC2APA102: " << name << endl << setw(4) << params << endl;
        osc2apa102s[ name ].addPools( pools );
        osc2apa102s[ name ].setPool( params );
        
    } else {ofLogError("Config: ") << "unknown source type: " << name;}
    
    //set Pools for each sink:
    
    
}

void SinkFactory::addPools(map< string, Pool >& sourcePools) {
    
    for (auto& pool : sourcePools)
        pools[ pool.first ] = &pool.second;
    
}
