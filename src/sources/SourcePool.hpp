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

using namespace std;

class SourcePool {
    
public:
    
    SourcePool() = default;
    ~SourcePool() = default;
    
    void setup()
        { addGroup( "default" ); }
    void setup(const string& defaultGroupName)
        { addGroup( defaultGroupName ); }
    
    // Setup the Source Pool with a json file
    void setup(ofJson& config);
    
    void update();
    void draw();
    void exit();
    
protected:
    
    void add(const string& srcName, ...);
    void remove(const string& srcName);
    void remove(Source*);
    
private:
    
    Group* addGroup(const string& groupName)
        {groups.emplace( groupName , Group(groupName) );}
    
    map<string, Group>    groups;
    
    list<Sources::Syphon>      syphons;
    list<Sources::Player>      players;
    list<Sources::Network>     networkIns;
    list<Sources::Generator>   generators;

    map<string, Source*>  sources;
    
};

#endif /* SourcePool_hpp */
