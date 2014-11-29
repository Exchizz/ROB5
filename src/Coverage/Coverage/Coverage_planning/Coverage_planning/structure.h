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




class Room: public square{
public:
    Room(square&);
    square corners;
    pair<int, int> center;
    int distance;
};

struct compare{
    bool operator()(const Room &centerA, Room &centerB)
    {
        return centerA.distance > centerB.distance;
    }
};

class structure: public Image{
public:
    vector<Room> priority_Blok_area(vector<square> rooms);
    void who_is_my_neighbour(Image&,vector<Room> hallways);
    vector<Room> Lokale;
private:
    std::priority_queue<Room , vector<Room> , compare > blok_A;
    std::priority_queue<Room , vector<Room> , compare > blok_B;
    std::priority_queue<Room , vector<Room> , compare > blok_C;
    std::priority_queue<Room , vector<Room> , compare > blok_D;
    std::priority_queue<Room , vector<Room> , compare > blok_E;
    std::priority_queue<Room , vector<Room> , compare > Big_hall;
};

#endif /* defined(__Coverage_planning__structure__) */
