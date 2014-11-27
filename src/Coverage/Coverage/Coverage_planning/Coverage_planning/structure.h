//
//  structure.h
//  Coverage_planning
//
//  Created by Keerthikan Ratnarajah on 27/11/14.
//  Copyright (c) 2014 Keerthikan Ratnarajah. All rights reserved.
//

#ifndef __Coverage_planning__structure__
#define __Coverage_planning__structure__

#include <stdio.h>
#include <iostream>
#include <queue>
#include <vector>
#include "Image.h"
#include "planning.h"
using namespace std;
class structure{
public:
    void priority_Blok_area(vector<square> rooms);
private:
    std::priority_queue<std::pair<int, int> > blok_A;
    std::priority_queue<std::pair<int, int> > blok_B;
    std::priority_queue<std::pair<int, int> > blok_C;
    std::priority_queue<std::pair<int, int> > blok_D;
    std::priority_queue<std::pair<int, int> > blok_E;
    std::priority_queue<std::pair<int, int> > blok_A_2;
    std::priority_queue<std::pair<int, int> > blok_B_2;
    std::priority_queue<std::pair<int, int> > blok_C_2;
    std::priority_queue<std::pair<int, int> > blok_D_2;
    std::priority_queue<std::pair<int, int> > blok_E_2;

};

#endif /* defined(__Coverage_planning__structure__) */
