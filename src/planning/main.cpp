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

	int cups = 0;
	Robot robot;
	for(auto room : img.listRooms){
		robot = img.cover_room(room);
		cups+=robot.cup_holder;
	}

	//std::cout << "Cup holder: " << cups << std::endl;

	//img.online_wavefront(75,100,170,300);
	//img.online_wavefront(100,100,200,200);
	//img.online_wavefront(666,900,1587,620);

	img.saveImage("img/output.pgm");

	//Planning wall;
	//wall.loadImage("img/test.pgm");
	//auto map = wall.wall_expansion();

	std::cout << "done" << std::endl;
	return 0;
}
