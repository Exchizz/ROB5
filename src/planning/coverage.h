/*
 * coverage.h
 *
 *  Created on: Dec 1, 2014
 *      Author: nicolai
 */

#ifndef COVERAGE_H_
#define COVERAGE_H_
#include "image.h"
#include "planning.h"

class Coverage {
public:
	Image * img;
	Coverage(Image *tmpimg){
		img = tmpimg;
	}
	int cover_room(Room &room);
	void draw_line(std::pair<int,int> from, std::pair<int,int> to);
};

#endif /* COVERAGE_H_ */
