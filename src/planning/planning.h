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
 *	141125		NAL		<Square> constructor updated to C++11 standard
 *
 *	------------------------------------------------------
 */

#ifndef ROOM_H_
#define ROOM_H_

/***************************** Include files *******************************/
#include <iostream>
#include <algorithm>
#include <queue>
#include "image.h"

/*****************************    Defines    *******************************/
#define BLACK 0
#define WHITE 255


#define BLOK_A		0
#define BIG_HALL 	1
#define BLOK_B		2
#define BLOK_C		3
#define BLOK_D		4
#define BLOK_E		5

#define ROBOT_DIA	8
#define ROBOT_RAD	(ROBOT_DIA/2)
/*****************************   Constants   *******************************/

/*****************************   Functions   *******************************/

class Room {
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
	int x1, y1, x2, y2, x3, y3, x4, y4;
	std::pair<int, int> center;
	int distance;

	Room(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4) :
			x1(x1), y1(y1), x2(x2), y2(y2), x3(x3), y3(y3), x4(x4), y4(y4), distance(0) {
	}

};

struct compare {
	bool operator()(const Room &centerA, Room &centerB) {
		return centerA.distance > centerB.distance;
	}
};



class Planning: public Image {
private:
	std::priority_queue<Room, std::vector<Room>, compare> blok_A;
	std::priority_queue<Room, std::vector<Room>, compare> blok_B;
	std::priority_queue<Room, std::vector<Room>, compare> blok_C;
	std::priority_queue<Room, std::vector<Room>, compare> blok_D;
	std::priority_queue<Room, std::vector<Room>, compare> blok_E;
	std::priority_queue<Room, std::vector<Room>, compare> Big_hall;

	std::vector<Room> listHallways;
	std::pair<int,int> drive_up(std::pair<int,int>);
	std::pair<int,int> drive_down(std::pair<int,int>);
	std::pair<int,int> drive_right(std::pair<int,int>);
public:
	int state = 0;
	std::vector<Room> listRooms;
	// Room detection
	bool is_black(int, int);
	void detect_rooms();
	void detect_center();
	void detect_hallways();
	void detect_neighbours();
	void draw_area(Room);
	void draw_line(std::pair<int,int>, std::pair<int,int>);
	void cover_room(Room);

	// Wavefront
	//void offline_wavefront();
	//void online_wavefront();
};

#endif
