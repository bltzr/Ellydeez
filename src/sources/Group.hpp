//
//  Group.hpp
//  Ellydeez
//
//  Created by Pascal Baltazar on 11/07/2018.
//

#ifndef Group_hpp
#define Group_hpp

#include <stdio.h>
//#include "SourceBase.hpp"
//#include "SourcePool.hpp"

class SourcePool;
class Source;

class Group {
    
public:

    Group(std::string name):
        groupName{name}{}
    
    ofPixels& getPixels() {return pixels;}
    std::string getName() {return groupName;}
    
protected:
    
    void add(Source*);
    void remove(Source*);
    void moveTo(Source*, Group*);
    
private:
    
    std::string groupName;
    ofPixels pixels;
    
    friend class SourcePool;

};

#endif /* Group_hpp */
