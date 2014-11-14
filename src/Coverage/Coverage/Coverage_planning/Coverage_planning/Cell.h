//
//  Cell.h
//  Coverage_planning
//
//  Created by Keerthikan Ratnarajah on 14/11/14.
//  Copyright (c) 2014 Keerthikan Ratnarajah. All rights reserved.
//

#ifndef __Coverage_planning__Cell__
#define __Coverage_planning__Cell__

#include <stdio.h>
#include "Coverage.h"
#include "Image.h"
#include <list>


using namespace std;
class Cell{
public:
    Cell();
    list<int> floor;
    list<int> Ceeling;
private:
    bool visited;
    bool cleaned;
};


#endif /* defined(__Coverage_planning__Cell__) */