//
//  SinkBase.cpp
//  Ellydeez
//
//  Created by Pascal Baltazar on 13/07/2018.
//

#include "SinkBase.hpp"


void Sink::addPools(map< string, Pool* >& sourcePools) {
    
    for (auto& pool : sourcePools)
        pools[ pool.first ] = pool.second;
    
}
