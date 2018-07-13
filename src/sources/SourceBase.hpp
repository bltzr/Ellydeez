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
//#include "SourcePool.hpp"
#include "Group.hpp"

class SourcePool;
class Group;

class Source {
    
public:
    
    void init();
    void update();
    void draw();
    void exit();
    
protected:
    
    int Xsize{1};
    int Ysize{0};
    Group group;
    
private:
    
    friend class SourcePool;
    
};
    
#endif /* SourceBase_hpp */
