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
	img.loadImage("img/complete_map_project.pgm");
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
	std::cout << img.listHallways[0].center.first << " " << img.listHallways[0].center.second << std::endl;
	//img.online_wavefront(75,100,170,300);
	//img.online_wavefront(700,200,900,300);
	//img.online_wavefront(700,1200,900,1000);

	img.online_wavefront(std::make_pair(700,1200),std::make_pair(900,1000));
	//img.online_wavefront(std::make_pair(90,119),std::make_pair(128,55));
	//img.online_wavefront(std::make_pair(1,2),std::make_pair(3,4));
	//img.online_wavefront(900,1000,1100,1150);
	//img.online_wavefront(2150,1400,780,571);

	/*
	// ONLINE
	// 1. Move from start position to first hallway
	// DEFINE::: Start pos = offload station
	std::pair <int,int> offload;
	offload.first = 2150;
	offload.second = 1400;
	Robot robot;

	int hallIt = 0;
	std::pair<int,int> end_coordinate;
	end_coordinate = img.online_wavefront(offload.first,offload.second,img.listHallways[hallIt].center.first,img.listHallways[hallIt].center.second);
		// 2. Run through listQueues
		for(auto queue : img.listQueues){
			while(!queue.empty()){
				// Move from previous position to upper left corner of room in priority queue
				end_coordinate = img.online_wavefront(end_coordinate.first,end_coordinate.second,queue.top().x2,queue.top().y2);
				// Cover room (top element in queue)
				robot = img.cover_room(queue.top());
				end_coordinate=std::make_pair(robot.endX,robot.endY);
				// Pop element
				queue.pop();
				// Save an image every time a room has been covered???
			}
			// Queue is empty = all rooms in current hallway has been covered.
			// Move to next hallway
			hallIt++;
			std::cout << hallIt << std::endl;
			end_coordinate = img.online_wavefront(end_coordinate.first,end_coordinate.second,img.listHallways[hallIt].center.first,img.listHallways[hallIt].center.second);
		}

	*/

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
