/*
 * coverage.cpp
 *
 *  Created on: Dec 1, 2014
 *      Author: nicolai
 */

#include "coverage.h"


void Coverage::draw_line(std::pair<int,int> from, std::pair<int,int> to){
	float slope = float(to.first - from.first)/float(to.second-from.second);
	//std::cout << "slope: " << slope << std::endl;
	for(int x = from.first; x < to.first; ++x){
		//std::cout << "x,y: " << x << " " << x*slope << std::endl;
		img->setPixel(x, x*slope,0);
	}
}

int Coverage::cover_room(Room &room){
	int px_moves;
	//Go to upper left corner
	//draw_line(room.center,std::make_pair(room.corners.x1, room.corners.y1));
	for(int globalx = room.x1; globalx < room.x4; globalx+=16 ){
		int globalTemp = globalx + 8;
		for(int globaly = room.y1; globaly <= room.y2; globaly++){
			for(int x = globalx; x < globalx+8; x++){
				if(x > 499){
					std::cout << "hit wall\n";
					return 0;
				}
				std::cout << "up: x,y: " << x << " " << globaly << std::endl;
				img->setPixel(x,globaly, 150);
			}
			img->setPixel(globalx + 4,globaly, 0);
		}
		for(int globaly = room.y2; globaly >= room.y1; globaly--){
			std::cout << "y: " << globaly << std::endl;
			for(int x = globalx+8; x < globalx+16; x++){
				std::cout << "globalx: " << x << std::endl;
				if(x > 499){
					std::cout << "hit wall\n";
					return 0;
				}
				std::cout << "down: x,y: " << x << " " << globaly << std::endl;
				img->setPixel(x,globaly, 150);
			}
			img->setPixel(globalx + 4,globaly, 0);
		}
	}
	return px_moves;
}
