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
	img.loadImage("img/dm_test.pgm");
	img.detect_rooms();
	img.detect_center();
	//img.detect_hallways();
	//img.detect_neighbours();

	for(int i=0; i<=55; i++){
		img.cover_room(img.listRooms[i]);
	}


	//Coverage cov(img);
	//cov.cover_room()

	img.saveImage("img/output.pgm");
	std::cout << "done" << std::endl;
	return 0;
}
