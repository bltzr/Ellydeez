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
#include "SourceBase.hpp"
#include "Syphon.hpp"
#include "Group.hpp"

class SourcePool {
    
public:
    
    void init();
    void update();
    void draw();
    void exit();
    
protected:
    
    void add(std::string srcName, ...);
    void remove(std::string srcName);
    void remove(Source*);
    
private:
    
    std::map<std::string, Source*> sources;
    std::map<std::string, Group*>  groups;
    
    std::list<Sources::Syphon> syphons;
    std::list<Sources::Player> players;
//    std::list<Sources::Network> netIns;
//    std::list<Sources::Generator> generators;

    
    
};

#endif /* SourcePool_hpp */
