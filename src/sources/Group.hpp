//
//  Group.hpp
//  Ellydeez
//
//  Created by Pascal Baltazar on 11/07/2018.
//

#ifndef Group_hpp
#define Group_hpp

#include <stdio.h>
#include <list>
#include "ofMain.h"
//#include "SourceBase.hpp"
//#include "SourcePool.hpp"

class SourcePool;
class Source;

class Group {
    
public:

    Group(std::string name):
        groupName{name}{}
    
    ofPixels& getPixels() {return pixels;}
    
    // if we want to be able to change the name, we must update it
    // in all registered Sources and all client Sinks
    std::string getName() {return groupName;}
    
    void setActiveSource(Source* src) {activeSource = src;}
    Source* getActiveSource() {return activeSource;}
    
protected:
    
    void add(Source*);
    void remove(Source*);
    void moveTo(Source*, Group*);
    
private:
    
    std::string         groupName;
    
    std::list<Source*>  sources;
    Source*             activeSource;
    
    ofPixels            pixels;
    
    
    friend class SourcePool;

};

#endif /* Group_hpp */
