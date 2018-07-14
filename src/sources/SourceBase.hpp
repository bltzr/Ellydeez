//
//  SourceBase.hpp
//  Ellydeez
//
//  Created by Pascal Baltazar on 11/07/2018.
//

#ifndef SourceBase_hpp
#define SourceBase_hpp

#include <stdio.h>
#include "ofMain.h"
#include "Group.hpp"

class SourcePool;
class Group;

class Source {
    
public:
    
    Source(Group* sourceGroup):
    group{sourceGroup}
    {}
    
    virtual ~Source() = 0;
    
    virtual void setup() = 0;
    virtual void update() = 0;
    virtual void draw() = 0;
    virtual void exit() = 0;
    
protected:
    
    int Xsize{1};
    int Ysize{0};
    Group* group;
    
private:
    
    friend class SourcePool;
    
};
    
#endif /* SourceBase_hpp */
