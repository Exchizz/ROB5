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
class structure: public Image{
public:
    vector<square> priority_Blok_area(vector<square> rooms);
    void who_is_my_neighbour(Image & ,vector<pair<int, int>> , vector<pair<int, int>> );
    void Spiral( int X, int Y,Image &map);
private:
    [std::priority_queue<std::pair<int, int> greater<pair<int, int>>> blok_A;
    std::priority_queue<std::pair<int, int> > blok_B;
    std::priority_queue<std::pair<int, int> > blok_C;
    std::priority_queue<std::pair<int, int> > blok_D;
    std::priority_queue<std::pair<int, int> > blok_E;
};

#endif /* defined(__Coverage_planning__structure__) */
