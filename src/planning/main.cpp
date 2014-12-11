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

	/*int cups = 0;
	for(int x = 0; x < img.getWidth(); x++){
		for(int y=0; y< img.getHeight(); y++){
			if(img.getPixel(x,y)==CUP)
				cups++;
		}
	}

	std::cout << "CUPS: " << cups << std::endl;*/

	Planning expandImg;
	expandImg.Copyconstructor(img);
	expandImg.wall_expansion();

	expandImg.saveImage("img/expand_v3.pgm");

	img.detect_rooms();
	img.detect_center();
	img.detect_hallways();
	img.detect_neighbours();



	// ONLINE
	// 1. Move from start position to first hallway
	// DEFINE::: Start pos = offload station
	std::pair <int,int> offload_left = std::make_pair(2400,1300);
	std::pair <int,int> offload_right = std::make_pair(2900,1300);

	int px_moves = 0;
	Robot robot;

	int hallIt = 0;
	std::pair<int,int> end_coordinate = expandImg.online_wavefront(offload_left, img.listHallways[hallIt].center,px_moves);
	// 2. Run through listQueues
	for(auto queue : img.listQueues){
		while(!queue.empty()){

			// Move from previous position to upper left corner of room in priority queue
			end_coordinate = expandImg.online_wavefront(end_coordinate,std::make_pair(queue.top().x2 + ROBOT_RAD,queue.top().y2 + ROBOT_RAD), px_moves);
			std::cout << "tmp x,y: " << end_coordinate.first << " " << end_coordinate.second << std::endl;
			// Cover room (top element in queue)
			robot = img.cover_room(queue.top(), px_moves, robot);
			std::cout << "I stopped in: " << robot.endX << " " << robot.endY << std::endl;
/*
			if(robot.full){
				std::cout << "Robot full" << std::endl;
				std::pair<int,int> tempPos = std::make_pair(robot.posX, robot.posY);
				std::pair<int,int> end;
				if(sqrt(pow((robot.posX - offload_left.first),2) + pow((robot.posY - offload_left.second),2))>sqrt(pow((robot.posX - offload_right.first),2) + pow((robot.posY - offload_right.second),2)))
					end = expandImg.online_wavefront(std::make_pair(robot.posX, robot.posY), offload_right,px_moves);
				else
					end = expandImg.online_wavefront(std::make_pair(robot.posX, robot.posY), offload_left,px_moves);

				robot.full = false;
				robot.cup_holder = 0;
				// Wavefront to tempPos
				expandImg.online_wavefront(end, tempPos, px_moves);

				// Complete coverage
				auto tmpRoom = queue.top();
				tmpRoom.x2 = tempPos.first - ROBOT_RAD;
				tmpRoom.y2 = tempPos.second - ROBOT_RAD;
				robot = img.cover_room(tmpRoom, px_moves, robot);
			}
			*/
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
		end_coordinate = expandImg.online_wavefront(end_coordinate,img.listHallways[hallIt].center,px_moves);
	}

	std::cout << "px moves: " << px_moves << std::endl;

	for(int x = 0; x < img.getWidth(); ++x){
		for(int y = 0; y < img.getHeight(); ++y){
			if(expandImg.getPixel(x,y) == 100){
				img.setPixel(x,y,100);
			}
		}
	}
	img.saveImage("img/output.pgm");
	expandImg.saveImage("img/expanted_v2.pgm");
	std::cout << "done" << std::endl;
	return 0;
}
