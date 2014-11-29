/*
 *	University of Southern Denmark
 *	Robotics in context
 *
 *	Project:		ROB5 - Cup Collector
 *	Module name:	planning.h
 *
 *	Description:
 *
 *	------------------------------------------------------
 *	Change Log:
 *
 *	Date		ID		Change
 *	YYMMDD
 *
 *	141123		NAL		Module Created
 *	141125		NAL		<square> constructor updated to C++11 standard
 *
 *	------------------------------------------------------
 */

#ifndef ROOM_H_
#define ROOM_H_


/***************************** Include files *******************************/
#include <iostream>
#include <algorithm>
#include <queue>
#include <stdio.h>
#include "image.h"
#include <vector>
/*****************************    Defines    *******************************/
#define BLACK 0
#define WHITE 255
#define BLOK_A      0
#define BIG_HALL    1
#define BLOK_B      2
#define BLOK_C      3
#define BLOK_D      4
#define BLOK_E      5
/*****************************   Constants   *******************************/

/*****************************   Functions   *******************************/


class square {
public:
    /*
     * Description of data members' placement in a square:
     *
     * 	(x1,y1)--------------(x4,y4)
     * 	   |					|
     * 	   |					|
     * 	   |					|
     *	(x2,y2)--------------(x3,y3)
     *
     */
    square();
    int x1, y1, x2, y2, x3, y3, x4, y4;
    square(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4)
    :x1(x1),y1(y1),x2(x2),y2(y2),x3(x3),y3(y3),x4(x4),y4(y4){}
};


class Room: public square{
public:
    Room(square&);
    square corners;
    std::pair<int, int> center;
    int distance;
};


struct compare{
    bool operator()(const Room &centerA, Room &centerB)
    {
        return centerA.distance > centerB.distance;
    }
};



class Planning: public Image {
public:
    std::vector<Room> priority_Blok_area(std::vector<square> rooms);
    void who_is_my_neighbour(std::vector<Room> hallways);
    std::vector<square> listSquares;
    int state = 0;
    bool is_black(int, int);
    std::vector<square> detect_rooms();
    std::vector<std::pair<int,int>> detect_center(std::vector<square>);
    void draw_area(square);
    // Wavefront
private:
    std::priority_queue<Room , std::vector<Room> , compare > blok_A;
    std::priority_queue<Room , std::vector<Room> , compare > blok_B;
    std::priority_queue<Room , std::vector<Room> , compare > blok_C;
    std::priority_queue<Room , std::vector<Room> , compare > blok_D;
    std::priority_queue<Room , std::vector<Room> , compare > blok_E;
    std::priority_queue<Room , std::vector<Room> , compare > Big_hall;
    std::vector<Room> Lokale;
    
};



#endif