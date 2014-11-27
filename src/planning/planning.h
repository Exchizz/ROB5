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
#include "image.h"

/*****************************    Defines    *******************************/
#define BLACK 0
#define WHITE 255

/*****************************   Constants   *******************************/

/*****************************   Functions   *******************************/


struct square {
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
	square(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4)
	:x1(x1),y1(y1),x2(x2),y2(y2),x3(x3),y3(y3),x4(x4),y4(y4){}
};

class Planning: public Image {
public:
	// Room detection
	std::vector<square> listSquares;
	int state = 0;
	bool is_black(int, int);
	void detect_rooms();
	void draw_area(square);
	// Wavefront

};



#endif
