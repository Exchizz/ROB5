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

/*****************************    Defines    *******************************/

/*****************************   Constants   *******************************/

/*****************************   Functions   *******************************/

int main() {
	Planning img;
	img.loadImage("img/test.pgm");

	auto listSquares = img.detect_rooms();
	auto listCenter = img.detect_center(listSquares);

	auto listHallways = img.detect_hallways(listSquares);
	auto listCenterHallways = img.detect_center(listHallways);

	//auto shortestDistances =
	img.detect_room_to_hallways(listCenter,listCenterHallways);

	img.saveImage("img/output.pgm");
	std::cout << "Hello world";
	return 0;
}
