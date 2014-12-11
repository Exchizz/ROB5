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
 *	141203		NAL		Inserted KR's functions (detect_hallways and detect_neighbours)
 *	141204		NAL		cover_room function added
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

#define MOVE_RIGHT	0
#define MOVE_UP		1
#define MOVE_DOWN	2

#define CUP			150
#define PATH		200
#define COVERAGE	220

#define OBSTACLE    1
#define FREE_SPACE  0

/*****************************   Constants   *******************************/

/*****************************   Functions   *******************************/

class Robot{
public:
	int direction;
	int posX,posY;
	int cup_holder=0;
	bool room_for_robot = true;
	int endX,endY;
	bool full = false;
};

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


class RobotWave{
public:
	int startX,startY;
	int goalX,goalY;
	int currX,currY;
};


class Planning: public Image {
private:
	std::priority_queue<Room, std::vector<Room>, compare> blok_A;
	std::priority_queue<Room, std::vector<Room>, compare> blok_B;
	std::priority_queue<Room, std::vector<Room>, compare> blok_C;
	std::priority_queue<Room, std::vector<Room>, compare> blok_D;
	std::priority_queue<Room, std::vector<Room>, compare> blok_E;
	std::priority_queue<Room, std::vector<Room>, compare> Big_hall;




	//std::pair<int,int> drive_up(std::pair<int,int>);
	//std::pair<int,int> drive_down(std::pair<int,int>);
	//std::pair<int,int> drive_right(std::pair<int,int>);
	Robot move_forward(Robot &robot, Room, int &px_moves);
	Robot draw_coverage(Robot &robot);
	void draw_area(Room);
	void draw_line(std::pair<int,int>, std::pair<int,int>);
public:
	int state = 0;
	std::vector<Room> listRooms;
	std::vector<std::priority_queue<Room, std::vector<Room>, compare>> listQueues;
	std::vector<Room> listHallways;

	// Room detection
	bool is_black(int, int);
	void detect_rooms();
	void detect_center();
	void detect_hallways();
	void detect_neighbours();

	//Planning(const Planning &planning){

	//}

	void Copyconstructor(const Planning &planning);

	//Coverage
	Robot cover_room(Room, int &px_moves, Robot &robot);

	// Navigation
	//void offline_wavefront();
	//std::pair<int,int> online_wavefront(int,int,int,int);
	void wall_expansion();
	int moveRobot(std::vector<std::vector <int> > & waveMap, std::pair<int,int> Qstart, std::pair<int,int> Qend);
	std::pair<int,int> online_wavefront(std::pair<int,int> start, std::pair<int,int> end, int& px_moves);
	bool inImage(int x, int y);
};

#endif
