/*
 *	University of Southern Denmark
 *	Robotics in context
 *
 *	Project:		ROB5 - Cup Collector
 *	Module name:	main.cpp
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
 *						Updated for multiple OS
 *
 *	------------------------------------------------------
 */

/***************************** Include files *******************************/
#include <iostream>
#include <vector>
#include "image.h"
#include "planning.h"
#include "coverage.h"

/*****************************    Defines    *******************************/

/*****************************   Constants   *******************************/

/*****************************   Functions   *******************************/

int main() {
	Planning img;
	img.loadImage("img/complete_map_project_fixing_rooms.pgm");
	//img.loadImage("img/world1.pgm");
	for(int x = 0; x<img.getWidth();x++){
		for(int y = 0; y<img.getHeight();y++){
			if(img.getPixel(x,y)!= WHITE and img.getPixel(x,y)!= BLACK and img.getPixel(x,y)!= CUP){
				img.setPixel(x,y,WHITE);
			}
		}
	}

	//img.saveImage("img/transformed_map.pgm");
	img.detect_rooms();
	img.detect_center();
	img.detect_hallways();
	img.detect_neighbours();
	//std::cout << img.listHallways[0].center.first << " " << img.listHallways[0].center.second << std::endl;

	// ONLINE
	// 1. Move from start position to first hallway
	// DEFINE::: Start pos = offload station
	std::pair <int,int> offload;
	offload.first = 2150;
	offload.second = 1400;
	int px_moves = 0;
	Robot robot;

	int hallIt = 0;
	std::pair<int,int> end_coordinate = img.online_wavefront(offload, img.listHallways[hallIt].center,px_moves);
	// 2. Run through listQueues
	for(auto queue : img.listQueues){
		while(!queue.empty()){

			// Move from previous position to upper left corner of room in priority queue
			end_coordinate = img.online_wavefront(end_coordinate,std::make_pair(queue.top().x2,queue.top().y2), px_moves);
			// Cover room (top element in queue)
			robot = img.cover_room(queue.top(), px_moves);
			end_coordinate = std::make_pair(robot.endX,robot.endY);
			// Pop element
			queue.pop();
			// Save an image every time a room has been covered???
		}
		// Queue is empty = all rooms in current hallway has been covered.
		// Move to next hallway
		hallIt++;
		std::cout << hallIt << std::endl;
		if(hallIt==6) // <<-Do we know why we need this?
			break;
		std::cout << "from queue: x:" << queue.top().center.first << " y: " << queue.top().center.second << std::endl;
		end_coordinate = img.online_wavefront(end_coordinate,img.listHallways[hallIt].center,px_moves);
	}

	std::cout << "px moves: " << px_moves << std::endl;
	/*int cups = 0;
	Robot robot;
	for(auto room : img.listRooms){
		robot = img.cover_room(room);
		cups+=robot.cup_holder;
	}*/

	//std::cout << "Cup holder: " << cups << std::endl;

	//img.online_wavefront(100,100,200,200);
	//img.online_wavefront(666,900,1587,620);

	img.saveImage("img/output.pgm");

	//Planning wall;
	//wall.loadImage("img/test.pgm");
	//auto map = wall.wall_expansion();

	std::cout << "done" << std::endl;
	return 0;
}
