//
//  SourcePool.hpp
//  Ellydeez
//
//  Created by Pascal Baltazar on 11/07/2018.
//

#ifndef SourcePool_hpp
#define SourcePool_hpp

#include <stdio.h>
#include <map>
#include <list>

#include "Group.hpp"

#include "Syphon.hpp"
#include "Player.hpp"
#include "Network.hpp"
#include "Generator.hpp"

class SourcePool {
    
public:
    
    SourcePool() = default;
    ~SourcePool() = default;
    
    void setup()
        {groups.emplace( "default" , Group("default") );}
    void setup(std::string defaultGroupName)
        {groups.emplace( defaultGroupName , Group(defaultGroupName) );}
    
    // Setup the Source Pool with a json file
    void setup(ofJson& config);
    
    void update();
    void draw();
    void exit();
    
protected:
    
    void add(std::string srcName, ...);
    void remove(std::string srcName);
    void remove(Source*);
    
private:
    
    std::map<std::string, Group>    groups;
    
    std::list<Sources::Syphon>      syphons;
    std::list<Sources::Player>      players;
    std::list<Sources::Network>     networkIns;
    std::list<Sources::Generator>   generators;

    std::map<std::string, Source*>  sources;
    
};

#endif /* SourcePool_hpp */
