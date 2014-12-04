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
#include <math.h>
#include "image.h"
#include "planning.h"

/*****************************    Defines    *******************************/

/*****************************   Constants   *******************************/

/*****************************   Functions   *******************************/

bool Planning::is_black(int x, int y) {
	if (x >= this->getWidth()) {
		std::cout << "Error: Width out of range\n";
		std::cout << "req. " << x << " max: " << getWidth() << std::endl;
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
	// std::cout << std::endl;
	// std::cout << "x: " << std::min(temp.x1, temp.x4) << "," << std::max(temp.x1, temp.x4) << std::endl;
	// std::cout << "y: " << std::min(temp.y1, temp.y2) << "," << std::max(temp.y1, temp.y2) << std::endl;

	for (int x = std::min(temp.x1, temp.x4); x < std::max(temp.x1, temp.x4) + 1;
			x++) {
		for (int y = std::min(temp.y1, temp.y2);
				y < std::max(temp.y1, temp.y2) + 1; y++) {
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

std::vector<std::pair<int, int>> Bresenham(int x1, int y1, int const x2,int const y2) {
	std::vector<std::pair<int, int>> dataOut;
	int delta_x(x2 - x1);
	// if x1 == x2, then it does not matter what we set here
	signed char const ix((delta_x > 0) - (delta_x < 0));
	delta_x = std::abs(delta_x) << 1;

	int delta_y(y2 - y1);
	// if y1 == y2, then it does not matter what we set here
	signed char const iy((delta_y > 0) - (delta_y < 0));
	delta_y = std::abs(delta_y) << 1;

	dataOut.push_back(std::make_pair(x1, y1));

	if (delta_x >= delta_y) {
		// error may go below zero
		int error(delta_y - (delta_x >> 1));

		while (x1 != x2) {
			if ((error >= 0) && (error || (ix > 0))) {
				error -= delta_x;
				y1 += iy;
			}
			// else do nothing

			error += delta_y;
			x1 += ix;

			dataOut.push_back(std::make_pair(x1, y1));
		}
	} else {
		// error may go below zero
		int error(delta_x - (delta_y >> 1));

		while (y1 != y2) {
			if ((error >= 0) && (error || (iy > 0))) {
				error -= delta_y;
				x1 += ix;
			}
			// else do nothing

			error += delta_x;
			y1 += iy;

			dataOut.push_back(std::make_pair(x1, y1));
		}
	}
	return dataOut;
}



/*
 * 1. Detects all upper left corners of squares, then
 * 2. it detects the upper right and then the lower left corner.
 * 3. Finally it "computes" the last corner and stores them in a
 * data type called square (which contains a pair of coordinates to each corner)
 */
void Planning::detect_rooms() {
	std::pair<int, int> corner;
	std::vector<std::pair<int, int>> listCorners;

	//1. Find all upper left corners
	for (int x = 0; x < getWidth() - 2; x++) {
		for (int y = 2; y < getHeight(); y++) {
			if (is_black(x, y) and is_black(x + 1, y) and is_black(x + 2, y)
			and is_black(x, y - 1) and is_black(x, y - 2)
			and not is_black(x + 1, y - 1)) {
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
			if (xRU >= getWidth() - 1) {
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

		// 2.4 Store coordinates of square in a vector
		if (!outSideBox) {
			// 2.4.1 Check that there's minimum 4 pixels between corners
			if (std::abs(yLU - yLD) > 4 and std::abs(xLU - xRU) > 4) {
				// constructor of square receives: (x1,y1,x2,y2,x3,y3,x4,y4)
				listRooms.emplace_back(xLU - 1, yLU + 1, xLU - 1, yLD + 1,
						xRU - 1, yLD + 1, xRU - 1, yLU + 1);

				/*
				 * emplace_back() invokes the constructor related to the type of the vector,
				 * in this case <squares>. This means that the object is created directly in
				 * the vector rather than creating it and then pushing onto the list.
				 */

				// DEBUG: Print coordinates
				// std::cout << std::endl;
				// std::cout << "Corner LU: (" << xLU - 1 << "," << yLU + 1 << ")\n";
				// std::cout << "Corner RU: (" << xRU - 1 << "," << yLU + 1 << ")\n";
				// std::cout << "Corner LD: (" << xRU - 1 << "," << yLD + 1 << ")\n";
				// std::cout << "Corner RD: (" << xLU - 1 << "," << yLD + 1 << ")\n";
				// DEBUG: Color each corner
				//setPixel(xLU - 1, yLU + 1, 100);
				//setPixel(xRU - 1, yLU + 1, 100);
				//setPixel(xRU - 1, yLD + 1, 100);
				//setPixel(xLU - 1, yLD + 1, 200);
			}
		}
	}
	//DEBUG: Draw squares' area
	//for (auto room : listRooms) {
	//	draw_area(room);
	//}
}

void Planning::detect_center() {
	for (auto& room : listRooms) {
		int diffX = std::max(room.x1, room.x4) - std::min(room.x1, room.x4);
		int diffY = std::max(room.y1, room.y2) - std::min(room.y1, room.y2);

		//room.center.first = (diffX / 2) + std::min(room.x1, room.x4);
		//room.center.second = (diffY / 2) + std::min(room.y1, room.y2);

		room.center = std::make_pair((diffX / 2) + std::min(room.x1, room.x4),
				(diffY / 2) + std::min(room.y1, room.y2));

		// DEBUG
		//setPixel(room.center.first, room.center.second, 255);
		//std::cout << "Center: (" << room.center.first << "," << room.center.second << ")\n";
	}
}

void Planning::detect_hallways() {
	for (auto room : listRooms) {
		// Look at the relationships between the walls
		if (abs(room.y4 - room.y2) / abs((room.x3 - room.x1)) <= 22
				and abs(room.y4 - room.y2) / abs((room.x3 - room.x1)) >= 7) {
			//std::cout << "hallway" << std::endl;

			listHallways.push_back(room);
		}

		//detection of hall in the middle
		if (room.x2 == 969 and room.y2 == 1136 and room.x3 == 3755) {
			//std::cout << "hallway" << std::endl;
			listHallways.push_back(room);
		}
	}
}

void Planning::detect_neighbours() {
	std::vector<int> listDistances;
	listDistances.reserve(6);
	int j = 10000000;
	int iterator = 0;
	int hitA = 0;
	int hitB = 0;
	int hitC = 0;
	int hitD = 0;
	int hitE = 0;
	int hitBig_hall = 0;

	std::cout << listHallways.size() << std::endl;

	// std::vector<priority_queue> hallQueue
	// for (auto hallway : listHallways){
	// 	hallQueue.push_back
	//}

	for (auto& room : listRooms) {
		// std::cout << "Room: " << i << std::endl;
		//Calculate distance to hallways.
		for (auto hallway : listHallways) {
			//std::cout << "hallway x: " << hallway.center.first  << " room x: " << room.center.first << std::endl;
			listDistances.push_back(sqrt(pow(abs(hallway.center.first - room.center.first),2)+ pow(abs(hallway.center.second- room.center.second),2)));
		}

		int min_dist = *std::min_element(listDistances.begin(),listDistances.end());
		int pos = distance(listDistances.begin(),std::min_element(listDistances.begin(),listDistances.end()));

		//std::cout << listDistances.size() << std::endl;
		//Determines smallest distance from list
		for (unsigned int k = 0; k < listDistances.size(); ++k) {
			//std::cout << "distance: " << listDistances[k] <<std::endl;
			if (listDistances[k] < j) {
				iterator = k;
				j = listDistances[k];
				//std::cout << k << "," << j << std::endl;
			}
		}
		std::cout << "min value: "<<min_dist << "," << listDistances[iterator] << std::endl;
		std::cout << "pos" << pos << "," << iterator << std::endl;

		//Insert room in priority_queue
		switch (iterator) {
		case BLOK_A:
			room.distance = listDistances[iterator];
			hitA++;
			blok_A.push(room);
			break;
		case BIG_HALL:
			room.distance = listDistances[iterator];
			hitBig_hall++;
			Big_hall.push(room);
			break;
		case BLOK_B:
			room.distance = listDistances[iterator];
			hitB++;
			blok_B.push(room);
			break;
		case BLOK_C:
			room.distance = listDistances[iterator];
			hitC++;
			blok_C.push(room);
			break;
		case BLOK_D:
			room.distance = listDistances[iterator];
			hitD++;
			blok_D.push(room);
			break;
		case BLOK_E:
			room.distance = listDistances[iterator];
			hitE++;
			blok_E.push(room);
			break;
		}
		// DEBUG
		//setPixel(room.center.first, room.center.second, BLACK);
		// Reset
		iterator = 0;
		j = 10000000;
		listDistances.clear();
	}
	//debug
	std::cout << hitA << " " << hitB << " " << hitC << " " << hitD << " " << hitE << " " << hitBig_hall << std::endl;
	std::cout << blok_A.size() << " " << blok_B.size() << " " << blok_C.size() << " " << blok_D.size() << " " << blok_E.size() << " " << Big_hall.size() << std::endl;

	/*
	//for (unsigned int i = 0; i< blok_A.size(); ++i){
	while(!blok_A.empty()){
		auto drawList = Bresenham(listHallways[BLOK_A].center.first, listHallways[BLOK_A].center.second,blok_A.top().center.first,blok_A.top().center.second);
		for(auto pixel : drawList){
			setPixel(pixel.first,pixel.second, 0);
		}
		blok_A.pop();
	}

	while(!Big_hall.empty()){
		auto drawList = Bresenham(listHallways[1].center.first, listHallways[1].center.second,Big_hall.top().center.first,Big_hall.top().center.second);
		for(auto pixel : drawList){
			setPixel(pixel.first,pixel.second, 0);
		}
		Big_hall.pop();
	}

	while(!blok_B.empty()){
		auto drawList = Bresenham(listHallways[BLOK_B].center.first, listHallways[BLOK_B].center.second,blok_B.top().center.first,blok_B.top().center.second);
		for(auto pixel : drawList){
			setPixel(pixel.first,pixel.second, 0);
		}
		blok_B.pop();
	}

	while(!blok_C.empty()){
		auto drawList = Bresenham(listHallways[BLOK_C].center.first, listHallways[BLOK_C].center.second,blok_C.top().center.first,blok_C.top().center.second);
		for(auto pixel : drawList){
			setPixel(pixel.first,pixel.second, 0);
		}
		blok_C.pop();
	}
	while(!blok_D.empty()){
		auto drawList = Bresenham(listHallways[BLOK_D].center.first, listHallways[BLOK_D].center.second,blok_D.top().center.first,blok_D.top().center.second);
		for(auto pixel : drawList){
			setPixel(pixel.first,pixel.second, 0);
		}
		blok_D.pop();
	}

	while(!blok_E.empty()){
		auto drawList = Bresenham(listHallways[BLOK_E].center.first, listHallways[BLOK_E].center.second,blok_E.top().center.first,blok_E.top().center.second);
		for(auto pixel : drawList){
			setPixel(pixel.first,pixel.second, 0);
		}
		blok_E.pop();
	}
	std::cout << blok_A.size() << " " << blok_B.size() << " " << blok_C.size() << " " << blok_D.size() << " " << blok_E.size() << " " << Big_hall.size() << std::endl;
	std::cout << listRooms.size() << std::endl;
	*/

	/*	for (unsigned int i = 0; i< blok_A.size(); ++i){
	 draw_line(listHallways[0].center,blok_A.top().center);
	 blok_A.pop();
	 }*/
	/*for (unsigned int i = 0; i < blok_E.size(); ++i) {
		setPixel(blok_E.top().center.first, blok_E.top().center.second, BLACK);
		blok_E.pop();
	}*/
}

Robot Planning::draw_coverage(Robot robot){
	for(signed int tempY = robot.posY-ROBOT_RAD; tempY < robot.posY+ROBOT_RAD; tempY++){
		for(signed int tempX = robot.posX-ROBOT_RAD; tempX < robot.posX+ROBOT_RAD; tempX++){
			if(getPixel(tempX,tempY)==WHITE or getPixel(tempX,tempY)==COVERAGE){
				setPixel(tempX,tempY,COVERAGE);
			}else if(getPixel(tempX,tempY) == CUP){
				robot.cup_holder++;
				setPixel(tempX,tempY,COVERAGE);
			}
		}
	}
	return robot;
}

Robot Planning::move_foreward(Robot robot,Room room){
	switch(robot.direction){
	case MOVE_RIGHT:
	{
		int boundary = ROBOT_DIA+robot.posX;
		while(robot.posX < boundary){
			robot = draw_coverage(robot);
			robot.posX++;
			if(room.x3 - robot.posX <= ROBOT_RAD){
				robot.room_for_robot = false;
				//std::cout << "No more room\n";
				break;
			}
			setPixel(robot.posX,robot.posY,PATH);
		}
		break;
	}
	case MOVE_UP:
	{
		int boundary = room.y1 - ROBOT_RAD;
		while(robot.posY < boundary){
			robot = draw_coverage(robot);
			robot.posY++;
			setPixel(robot.posX, robot.posY,PATH);
		}
		break;
	}
	case MOVE_DOWN:
	{
		int boundary = ROBOT_RAD+room.y2;
		while(robot.posY > boundary){
			robot = draw_coverage(robot);
			robot.posY--;
			setPixel(robot.posX, robot.posY,PATH);
		}

		break;
	}
	}
	return robot;
}

Robot Planning::cover_room(Room room){
	Robot robot;

	// Initialize starting position
	robot.posX = room.x2+ROBOT_RAD;
	robot.posY = room.y2+ROBOT_RAD;

	// 1.2 Initial Coverage
	for(signed int tempY = robot.posY-ROBOT_RAD; tempY < robot.posY+ROBOT_RAD; tempY++){
		for(signed int tempX = robot.posX-ROBOT_RAD; tempX < robot.posX+ROBOT_RAD; tempX++){
			setPixel(tempX,tempY,COVERAGE);
		}
	}

	while(robot.room_for_robot){
		robot.direction = MOVE_UP;
		robot=move_foreward(robot,room);
		robot.direction = MOVE_RIGHT;
		robot=move_foreward(robot,room);
		if(!robot.room_for_robot){
			// DEBUG
			//std::cout << "Breaking out of loop\n";
			break;
		}
		robot.direction = MOVE_DOWN;
		robot=move_foreward(robot,room);
		robot.direction = MOVE_RIGHT;
		robot=move_foreward(robot,room);
	}

	//compute remaining lanes.

	int diffX = room.x3 - ROBOT_RAD - robot.posX;
	int diffY = room.y3 + ROBOT_RAD - robot.posY;
	//std::cout << room.x3 << " " << robot.posX << " " << diffX << std::endl;
	//std::cout << room.y3 << " " << robot.posY << " " << diffY << std::endl;

	if(robot.direction == MOVE_RIGHT){
		if(diffX == 0 and diffY != 0){
			robot.direction = MOVE_DOWN;
			robot = move_foreward(robot,room);
		}
		if(diffX == 0 and diffY == 0){
			robot.direction = MOVE_UP;
			robot = move_foreward(robot,room);
		}
	}
	robot.endX = robot.posX;
	robot.endY = robot.posY;
	//std::cout << "Cup holder: " << robot.cup_holder << std::endl;
	return robot;
}

void Planning::online_wavefront(int startPOSX,int startPOSY, int goalPOSX,int goalPOSY){
	std::cout << "Initialize...\n";
	// 1. Initialize
	// 1.1 Set start and goal for robot
	RobotWave robot;
	robot.startX = startPOSX;
	robot.startY = startPOSY;
	robot.currX = robot.startX;
	robot.currY = robot.startY;
	robot.goalX = goalPOSX;
	robot.goalY = goalPOSY;

	// 1.2 Create copy of map
	int** map_copy = new int*[getWidth()];
	for (int i = 0; i < getWidth(); i++)
		map_copy[i] = new int[getHeight()];

	// 1.2.1 Transform the map to One's and Zero's
	for (int y = 0; y < getHeight(); y++){
		for (int x = 0; x < getWidth(); x++){
			if (getPixel(x, y) == 255)
				map_copy[x][y] = 0;
			else
				map_copy[x][y] = 1;
		}
	}

	// 1.3 Label the goal with a two
	map_copy[robot.goalX][robot.goalY] = 2;

	// 1.4 Create buffers that will hold locations of last visited values
	std::vector<std::pair<int,int>> buffer_write;


	// 1.5 Put goal into buffer
	buffer_write.push_back(std::make_pair(robot.goalX,robot.goalY));


	int incValue = 2;

	std::cout << "Create wave...\n";
	//Make the wave
	//Run until robot's location has a value
	int tempX, tempY;
	while (map_copy[robot.currX][robot.currY] == 0)
	{
		incValue++;
		//Copy write buffer to read buffer
		std::vector<std::pair<int,int>> buffer_read (buffer_write);
		buffer_write.clear();

		//Go through all coordinates set in previous iteration
		for(auto coord : buffer_read)
		{
			//Location to inspect is loaded
			std::pair<int,int> location = std::make_pair(coord.first,coord.second);

			//Do for each connection (four in this case)
			for ( int i = 0; i < 4; i++ )
			{
				switch (i)
				{
				case 0:
					tempY = location.second - 1;
					tempX = location.first;
					break;
				case 1:
					tempY = location.second + 1;
					tempX = location.first;
					break;
				case 2:
					tempY = location.second;
					tempX = location.first - 1;
					break;
				case 3:
					tempY = location.second;
					tempX = location.first + 1;
					break;
				}
				//If connected pixel is not a wall or obstacle set value to incValue(the incrementing value)
				if (tempX <= getWidth() - 1 && tempY <= getHeight() - 1 && tempX > 0 && tempY > 0)
				{
					//only if there is no value there
					if (map_copy[tempX][tempY] == 0)
					{
						map_copy[tempX][tempY] = incValue;
						buffer_write.push_back(std::make_pair(tempX,tempY));
					}
				}
			}
		}
	}

	std::cout << "Run through wave...\n";
	// Plan/Run route
	while (true)
	{
		//Get value at robots location
		incValue = map_copy[robot.currX][robot.currY];
		// For all connecting points try to find a value that is less than the current
		// Directions up and right are preferred
		// When found change pixelvalue and increment moves
		for (int i = 0; i < 4; i++)
		{
			switch (i){
			case 3:
				tempY = robot.currY - 1;
				tempX = robot.currX;
				break;
			case 1:
				tempY = robot.currY + 1;
				tempX = robot.currX;
				break;
			case 2:
				tempY = robot.currY;
				tempX = robot.currX - 1;
				break;
			case 0:
				tempY = robot.currY;
				tempX = robot.currX + 1;
				break;
			}
			if (tempX <= getWidth() - 1 && tempY <= getHeight() - 1 && tempX > 0 && tempY > 0){
				if (incValue > map_copy[tempX][tempY] && map_copy[tempX][tempY] != 1){
					robot.currX = tempX;
					robot.currY = tempY;
					setPixel(tempX, tempY, 80);
					break;
				}
			}
		}
		//If goal is reached break loop
		if (robot.currX == robot.goalX and robot.currY == robot.goalY)
			break;
	}
}

int** Planning::wall_expansion() {
	int expansion_factor = 4;

	int** expand_map = new int*[getWidth()];

	for (int i = 0; i < getWidth(); i++){
		expand_map[i] = new int[getHeight()];
	}

	for(int x = 0; x < getWidth(); x++){
		for(int y = 0; y < getHeight(); y++){
			if(getPixel(x,y) <= 50){
				for(int i = 0; i<=expansion_factor;i++){
					for(int j = 0; j<=expansion_factor;j++){
						if(y+i <= getHeight()-1 && x+j <= getWidth()-1 ){expand_map[x+j][y+i] = 1;}
						if(y+i <= getHeight()-1 && x-j >= 0){expand_map[x-j][y+i] = 1;}
						if(y-i >= 0 && x-j >= 0 ){expand_map[x-j][y-i] = 1;}
						if(y-i >= 0 && x+j <= getWidth()-1 ){expand_map[x+j][y-i] = 1;}
					}
				}
			}else if(expand_map[x][y] != 1){
				expand_map[x][y] = 0;
			}
		}
	}
	return expand_map;
}
