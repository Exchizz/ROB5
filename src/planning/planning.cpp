/*
 *	University of Southern Denmark
 *	Robotics in context
 *
 *	Project:		ROB5 - Cup Collector
 *	Module name:	planning.cpp
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
 *	141126		NAL		Cleaned code
 *						Added comments
 *
 *	------------------------------------------------------
 */

/***************************** Include files *******************************/
#include <iostream>
#include <vector>
#include <map>
#include "image.h"
#include "planning.h"

/*****************************    Defines    *******************************/

/*****************************   Constants   *******************************/

/*****************************   Functions   *******************************/


bool Planning::is_black(int x, int y) {
	if (x >= this->getWidth()) {
		std::cout << "Error: Width out of range\n";
		return false;
	}
	if (y >= this->getHeight()) {
		std::cout << "Error: Height out of range\n";
		return false;
	}
	if (this->getPixel(x, y) == BLACK)
		return true;
	else
		return false;
}

void Planning::draw_area(Room temp) {
	//DEBUG: Print minimum and maximum values for coordinates (x,y)
	std::cout << std::endl;
	std::cout << "x: " << std::min(temp.x1, temp.x4) << "," << std::max(temp.x1, temp.x4) << std::endl;
	std::cout << "y: " << std::min(temp.y1, temp.y2) << "," << std::max(temp.y1, temp.y2) << std::endl;


	for (int x = std::min(temp.x1, temp.x4); x < std::max(temp.x1, temp.x4)+1;x++) {
		for (int y = std::min(temp.y1, temp.y2); y < std::max(temp.y1, temp.y2)+1;y++) {
			if (state == 0)
				setPixel(x, y, 50);
			else if (state == 1)
				setPixel(x, y, 100);
			else if (state == 2)
				setPixel(x, y, 150);
			else if (state == 3)
				setPixel(x, y, 200);
		}
	}
	state++;
	if (state > 3)
		state = 0;
}

/*
 * 1. Detects all upper left corners of Rooms, then
 * 2. it detects the upper right and then the lower left corner.
 * 3. Finally it "computes" the last corner and stores them in a
 * data type called Room (which contains a pair of coordinates to each corner)
 */
std::vector<Room> Planning::detect_rooms() {
	std::pair<int, int> corner;
	std::vector<std::pair<int, int>> listCorners;

	//1. Find all upper left corners
	for (int x = 0; x < getWidth(); x++) {
		for (int y = 0; y < getHeight(); y++) {
			if (is_black(x, y) and is_black(x + 1, y) and is_black(x + 2, y) and is_black(x, y - 1) and is_black(x, y - 2) and not is_black(x + 1, y - 1)) {
				// Upper left corner found
				corner = std::make_pair(x + 1, y - 1);
				// Push pair of coordinates of the corner onto vector
				listCorners.push_back(corner);
			}
		}
	}

	// 2. Loop through list of upper left corners and find remaining matching corners
	for (auto it = listCorners.begin(); it != listCorners.end(); ++it) {
		// 2.1 Initialize starting points
		std::pair<int, int> temp_corner = *it;
		int xLU = temp_corner.first + 1;
		int yLU = temp_corner.second - 1;
		int xRU = temp_corner.first + 1;
		int yLD = temp_corner.second - 1;
		bool outSideBox = false;

		// 2.2 	Detect upper right corner
		// 		Move horizontally right from (x+1,y-1) to first black pixel
		while (!is_black(xRU, yLU) and !outSideBox) {
			// 2.2.1 Check that we're still inside the image
			if (xRU >= getWidth()-1) {
				outSideBox = true;
				break;
			}
			xRU++;
		}
		// 2.3 	Detect lower left corner
		// 		Move vertically downwards from (x+1,y-1) to first black pixel
		while (!is_black(xLU, yLD) and !outSideBox) {
			// 2.3.1 Check that we're still inside the image
			if (yLD <= 0) {
				outSideBox = true;
				break;
			}
			yLD--;
		}


		// 2.4 Store coordinates of Room in a vector
		if (!outSideBox) {
			// 2.4.1 Check that there's minimum 4 pixels between corners
			if (std::abs(yLU - yLD) > 4 and std::abs(xLU - xRU) > 4) {
				// constructor of Room receives: (x1,y1,x2,y2,x3,y3,x4,y4)
				//listRooms.emplace_back(xLU - 1, yLU + 1, xLU - 1, yLD + 1, xRU - 1, yLD + 1, xRU - 1, yLU + 1);
				listRooms.push_back(Room(xLU - 1, yLU + 1, xLU - 1, yLD + 1, xRU - 1, yLD + 1, xRU - 1, yLU + 1));
				/*
				 * emplace_back() invokes the constructor related to the type of the vector,
				 * in this case <Rooms>. This means that the object is created directly in
				 * the vector rather than creating it and then pushing onto the list.
				 */

				// DEBUG: Print coordinates
				std::cout << std::endl;
				std::cout << "Corner LU: (" << xLU-1 << "," << yLU+1 << ")\n";
				std::cout << "Corner RU: (" << xRU-1 << "," << yLU+1 << ")\n";
				std::cout << "Corner LD: (" << xRU-1 << "," << yLD+1 << ")\n";
				std::cout << "Corner RD: (" << xLU-1 << "," << yLD+1 << ")\n";

				// DEBUG: Color each corner
				setPixel(xLU - 1, yLU + 1, 100);
				setPixel(xRU - 1, yLU + 1, 100);
				setPixel(xRU - 1, yLD + 1, 100);
				setPixel(xLU - 1, yLD + 1, 100);
			}
		}
	}
	//DEBUG: Draw Rooms' area
	for (auto Room : listRooms) {
		draw_area(Room);
	}

	//
	return listRooms;
}

std::vector<std::pair<int,int>> Planning::detect_center(std::vector<Room> listRooms){
	std::pair<int,int> center;
	std::vector<std::pair<int,int>> listCenters;

	for(auto Room : listRooms){
		int diffX = std::max(Room.x1, Room.x4) - std::min(Room.x1, Room.x4);
		int diffY = std::max(Room.y1, Room.y2) - std::min(Room.y1, Room.y2);

		center.first = (diffX/2) + std::min(Room.x1, Room.x4);
		center.second = (diffY/2) + std::min(Room.y1, Room.y2);
		listCenters.push_back(center);

		// DEBUG
		setPixel(center.first,center.second,255);
		std::cout << "Center: (" << center.first << "," << center.second << ")\n";
	}
	return listCenters;
}


std::vector<Room> Planning::detect_hallways(std::vector<Room> center_rooms){
	std::cout << "size of center_room:" << center_rooms.size() << std::endl;
	std::vector<Room> listHalls;
	for(auto room : center_rooms){
		if (abs(room.y4-room.y2)/abs((room.x3 - room.x1)) <= 22 and abs(room.y4-room.y2)/abs((room.x3 - room.x1)) >= 7) {
			listHalls.push_back(Room(room.x1,room.y1,room.x2,room.y2,room.x3,room.y3,room.x4,room.y4));
		}
	}
	return listHalls;
}

float Planning::dist_room_hall(std::pair<int,int> room, std::pair<int,int> hallway){
	return sqrt(pow(abs(room.first - hallway.first),2) + pow(abs(room.second - hallway.second),2));
}
/*
int Planning::getHallIdent(std::pair<int,int> hall){
	int retval = 0;
	static int uniq = 0;

	if(hallToRooms.find(hall) == hallToRooms.end()){
		hallToRooms[hall] = uniq;
		retval = uniq;
		uniq++;
		std::cout << uniq << std::endl;
	} else {
		retval = hallToRooms[hall];
	}
	return retval;
}
*/
/*
void Planning::detect_room_to_hallways(std::vector<std::pair<int,int>> rooms, std::vector<std::pair<int,int>> hallways){
	std::vector<RoomCenter> listRoomsCenter;
	for(auto room : rooms){

		std::vector<Room> tempRooms;
		for(auto hallway : hallways){
			int dist = dist_room_hall(room,hallway);

			RoomCenter roomcenter(room);
			roomcenter.setDistance(dist);
			roomcenter.setHallwayCenter(hallway);

			listRoomsCenter.push_back(roomcenter);
		}

	//	RoomCenter closestHallway;

		closestHallway = listRoomsCenter[0];

		for(auto roomCenter : listRoomsCenter){
			if(roomCenter.distance < closestHallway.distance){
				closestHallway = roomCenter;
			}
		}

		hallToRooms[closestHallway.hallwayCord].push_back(closestHallway.roomCenterCord);
	}
	//return hallToRooms;


}
*/
