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
 *	141205		NAL		Converted KR's code to C++11 std
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

	// Reserve memory for # priority queues
	listQueues.reserve(6);
	std::priority_queue<Room, std::vector<Room>, compare> blok_A,blok_B,blok_C,blok_D,blok_E,Big_hall;

	// HACK
	listQueues.push_back(blok_A);
	listQueues.push_back(Big_hall);
	listQueues.push_back(blok_B);
	listQueues.push_back(blok_C);
	listQueues.push_back(blok_D);
	listQueues.push_back(blok_E);

	for (auto& room : listRooms) {
		//Calculate distance from current room to all hallways.
		for (auto hallway : listHallways) {
			listDistances.push_back(sqrt(pow(abs(hallway.center.first - room.center.first),2)+ pow(abs(hallway.center.second- room.center.second),2)));
		}

		// Find smallest distance and the distance's position in list
		int min_dist = *std::min_element(listDistances.begin(),listDistances.end());
		int min_val_pos = distance(listDistances.begin(),std::min_element(listDistances.begin(),listDistances.end()));

		// Insert distance in room's data member
		room.distance = min_dist;
		// Insert room in appropriate priority queue
		listQueues[min_val_pos].push(room);

		// Clear list of distances for next room
		listDistances.clear();
	}
	// DEBUG
	for(auto queue : listQueues){
		std::cout << queue.size() << " ";
	}
	std::cout << std::endl;

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

//Method to move robot
void Planning::moveRobot(std::vector<std::vector <int> > & waveMap, std::pair<int,int> Qstart, std::pair<int,int> Qend){
	std::ofstream fileOut;
	fileOut.open("img/tmp_output.pgm");
	fileOut << "P2\n";
	fileOut << "# THE BEER-WARE LICENSE (Revision 42)\n";
	fileOut << getWidth() << " " << getHeight() << "\n";
	fileOut << 255 << "\n";

	for(auto vec : waveMap){
		for(auto elm : vec){
			fileOut << elm << " ";
		}
		fileOut << std::endl;
	}
	std::cout << "partially done" << std::endl;


	exit(0);
	int x = Qstart.first;
	int y = Qstart.second;

	std::cout << "Starting in (x,y): " << x << " " << y << std::endl;
	std::cout << "stopping in (x,y): " << Qend.first << " " << Qend.second << std::endl;

	int diffLeft = 0, diffRight = 0, diffUp = 0, diffDown = 0;
	int counter = 0;


	//While the robot aren't in goal.
	do{
		//Same checks as before and calculates difference.
		if(x > 0){
			diffLeft =  waveMap[x][y] -  waveMap[x-1][y];
			//image[x][y].first - image[x-1][y].first;
		}
		if(x < (getWidth() - 1)){
			diffRight = waveMap[x][y] - waveMap[x+1][y];
			//image[x][y].first - image[x+1][y].first;
		}
		if(y > 0){
			diffUp    =  waveMap[x][y] - waveMap[x][y-1];
			//image[x][y].first - image[x][y-1].first;
		}
		if(y < (getHeight() - 1)){
			diffDown  =  waveMap[x][y] - waveMap[x][y+1];
			//image[x][y].first - image[x][y+1].first;
		}
		//Draw where the robot is - notice second.
		//image[x][y].second = MAX_VALUE;

		//Make sure we don't go into an obstacle
		if(abs(diffUp) ==1 && abs(diffDown) == 1){
			//Detect where to move - up or down
			if(diffUp > diffDown){ // move down
				--y;
			}
			if(diffUp < diffDown) {
				++y;
			}
		}

		std::cout << "diffleft: " << diffLeft << " diffright: " << diffRight << std::endl;

		if(abs(diffLeft) == 1 && abs(diffRight) == 1){
			//Detect where to move - right or left
			if(diffLeft >= diffRight){ //move right
				--x;
			}
			if(diffLeft < diffRight){
				++x;
			}
		}
		std::cout << "x: " << x << " y: " << y << std::endl;

		//count number of steps
		++counter;

	}while(!(x == Qend.first && y == Qend.second));
	//saveImg("draw.pgm");

	std::cout << "count: " << counter << std::endl;
}
bool Planning::inImage(int x, int y){
	return (x < getWidth() and y < getWidth() and x >= 0 and y >= 0);
}


bool isDone(std::pair<int,int> start, int x, int y){
	return start.first == x && start.second == y ;
}

void Planning::online_wavefront(std::pair<int,int> start, std::pair<int,int> end){
	if(!inImage(start.first,start.second)){
		std::cout << "Wavefront: Qstart out of range..." << std::endl;
		exit(0);
	}

	if(!inImage(end.first,end.second)){
		std::cout << "Wavefront: Qend out of range..." << std::endl;
		exit(0);
	}

	std::vector<std::vector <int> > waveMap;

	for(int i = 0; i < getWidth(); i++){
		std::vector<int> col(getHeight());
		waveMap.push_back(col);
	}

	std::queue<std::pair<std::pair<int,int>, int>> queue;
	int last = 2;
	int x = 0;
	int y = 0;
	std::vector<std::pair<int,int>> lastPoint;

	waveMap[end.first][end.second] = 2;
	//waveMap[start.first][start.second] = 1;

	queue.push(std::make_pair(std::make_pair(end.first, end.second), last));

	//while(x != start.first and y != start.second){
	while(!queue.empty()){
		//for(int i = 0; i < 10; i++){
		//Get oldest element
		auto pair = queue.front();
		//remove oldest element
		queue.pop();

		std::cout << "queue size: " << queue.size() << std::endl;
		x = pair.first.first;
		y = pair.first.second;

		last = pair.second +1;
		if (inImage(x,y+1) && waveMap[x][y+1] == 0 && !is_black(x,y+1)){
			waveMap[x][y+1] = last;
			queue.push(std::make_pair(std::make_pair(x,y+1), last));
		}
		if (inImage(x,y-1) && waveMap[x][y-1] == 0 && !is_black(x,y-1) ){
			waveMap[x][y-1] = last;
			queue.push(std::make_pair(std::make_pair(x,y-1), last));
		}
		if (inImage(x+1,y) && waveMap[x+1][y] == 0  && !is_black(x+1,y)){
			waveMap[x+1][y] = last;
			queue.push(std::make_pair(std::make_pair(x+1,y), last));
		}
		if (inImage(x-1,y) && waveMap[x-1][y] == 0 && !is_black(x-1,y)){
			waveMap[x-1][y] = last;
			queue.push(std::make_pair(std::make_pair(x-1,y), last));
		}

		if(isDone(start,x,y+1) || isDone(start,x,y-1) || isDone(start,x+1, y) || isDone(start,x-1,y)){
			std::cout << "I'm out" << std::endl;
			break;
		}
		std::cout << "x: " << x << " y: " << y << " last: " << last << std::endl;
	}
	//moveRobot(waveMap,start, end);
	std::ofstream fileOut;
	fileOut.open("img/tmp_output.pgm");
	fileOut << "P2\n";
	fileOut << "# THE BEER-WARE LICENSE (Revision 42)\n";
	fileOut << getWidth() << " " << getHeight() << "\n";
	fileOut << 255 << "\n";

	for(int y = 0; y < getHeight(); y++){
		for(int x = 0; x <  getWidth(); x++){
			fileOut << waveMap[x][y] << " ";
		}
		fileOut << std::endl;
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
