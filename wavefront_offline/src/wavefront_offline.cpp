//============================================================================
// Name        : Wavefront offline
// Author      : jejep12
// Version     : v5
// Description : Wavefront: offline version
//============================================================================

#include "wavefront_offline.h"

// Position coordinates for unload--station 1
#define STATION1_X 2150
#define STATION1_Y 1400

// Position coordinates for unload--station 2
#define STATION2_X 3100
#define STATION2_Y 1400

#define XINIT 220
#define YINIT 1100

#define INFY 9999999

offlineWaveFront::offlineWaveFront(){

	std::cout << "Loading img" << std::endl;
	// img.loadImage("complete_map_project.pgm");

	img.loadImage("complete_map_project.pgm");

	xHeight = img.getHeight();
	xWidth = img.getWidth();

	std::cout << "Allocate the Array" << std::endl;

	// Allocation of the array
	arr = new int*[xHeight];	// New instans

	// Initialization of each position
	for (int i = 0; i < xHeight; ++i)
	{
		arr[i] = new int[xWidth];
		for (int j = 0; j < xWidth; ++j)
		{
			if (img.getPixel(j, i) != 0 && img.getPixel(j, i) != 150)
				arr[i][j] = 0;
			else
				arr[i][j] = 1;
		}
	}

}

offlineWaveFront::~offlineWaveFront(){
	// Clean up; deallocate the array and pointer
	for (int i = 0; i < xHeight; i++){
		delete[] arr[i];		// Delete each row
	}
	delete[] arr;		// Delete array pointer

	std::cout << "Cleaned up and Done" << std::endl;
}

int** offlineWaveFront::waveFront(int xRPOS, int yRPOS){

	int tmp = arr[xRPOS][yRPOS];

	arr[xRPOS][yRPOS] = INFY; 	// Place the Robot
	int xRobot = 0;
	int yRobot = 0;

	std::list<int> xBreadcrumb;
	std::list<int> yBreadcrumb;

	// Search the map for the locations of the robot
	for (int x = 0; x < xHeight; x++)
	{
		for (int y = 0; y < xWidth; y++)
		{
			if (arr[x][y] == INFY)
			{
				xRobot = x;
				yRobot = y;
			}
		}
	}

	int xPos = xRobot;
	int yPos = yRobot;
	int currentDir = 0;
	int nextDir = 0;
	int current_low = INFY;

	/*
	 * Find the path by looking at the value of the neighboring pixel and finding the
	 * next direction from which value that is the highest.
	 */

	while (current_low > 2)
	{
		current_low = INFY;
		nextDir = currentDir;
		int xNext = 0;
		int yNext = 0;

		// Left direction
		if (xPos > 0) //
			if (arr[xPos - 1][yPos] < current_low && arr[xPos - 1][yPos] != 1)
			{
				current_low = arr[xPos - 1][yPos]; // Set next number
				nextDir = 3; //Set next Direction
				xNext = xPos - 1;
				yNext = yPos;
				// A similar algorithm is repeated for each direction, so they are not commented.
			}

		// Right direction
		if (xPos < (xHeight - 1))
			if (arr[xPos + 1][yPos] < current_low && arr[xPos + 1][yPos] != 1)
			{
				current_low = arr[xPos + 1][yPos];
				nextDir = 1;
				xNext = xPos + 1;
				yNext = yPos;
			}

		// Down direction
		if (yPos > 0)
			if (arr[xPos][yPos - 1] < current_low && arr[xPos][yPos - 1] != 1)
			{
				current_low = arr[xPos][yPos - 1];
				nextDir = 2;
				xNext = xPos;
				yNext = yPos - 1;
			}

		// Up direction
		if (yPos < (xWidth - 1))
			if (arr[xPos][yPos + 1] < current_low && arr[xPos][yPos + 1] != 1)
			{
				current_low = arr[xPos][yPos + 1];
				nextDir = 0;
				xNext = xPos;
				yNext = yPos + 1;
			}

		xPos = xNext;
		yPos = yNext;

		img.setPixel(yPos,xPos, 50);

		// Trace the path back to the unload--station
		xBreadcrumb.push_back(xPos);
		yBreadcrumb.push_back(yPos);

		// Making the path from the nextDir values
		while (currentDir != nextDir)
		{
			if (currentDir > nextDir)
			{
				currentDir--;
			}
			else if (currentDir < nextDir)
			{
				currentDir++;
			}
		}
	}

	// Insert offLoad() function

	// Trace back to the position, where the coverage was stopped
	int sizeBreadcrumb = xBreadcrumb.size();
	for ( int i = 0; i < sizeBreadcrumb; i++) {
		//std::cout << i << " " << xBreadcrumb.front() << " " << yBreadcrumb.front() << std::endl;
		xBreadcrumb.pop_front();
		yBreadcrumb.pop_front();
	}


	std::cout << "WaveFront Done" << std::endl;

	// Reset the the loading stations and robot position on the map
	img.setPixel(STATION1_X, STATION1_Y, 2);	// Unload--station 1
	img.setPixel(STATION2_X, STATION2_Y, 2);	// Unload--station 2
	//img.setPixel(XINIT, YINIT, 2);

	// Set the position of the loading stations
	arr[STATION1_Y][STATION1_X] = 2;	// Unload--station 1
	arr[STATION2_Y][STATION2_X] = 2; 	// Unload--station 2

	arr[xRPOS][yRPOS] = tmp;

	return arr;
}


int** offlineWaveFront::init() {
	// Mark the the loading stations on the map
	img.setPixel(STATION1_X, STATION1_Y, 2);	// Unload--station 1
	img.setPixel(STATION2_X, STATION2_Y, 2);	// Unload--station 2
	//img.setPixel(XINIT, YINIT, 2);

	// Set the position of the loading stations
	arr[STATION1_Y][STATION1_X] = 2;	// Unload--station 1
	arr[STATION2_Y][STATION2_X] = 2; 	// Unload--station 2

	std::cout << "Grap a cup of Coffee, this is going to take a 'While'" << std::endl;

	// Generating the WaveFront
	int xWave, yWave;
	bool foundWave = true;
	int currentWave = 2; // First wave is the value of the goal

	/*
	 * THE PRINCIPLE IN THIS IMPLEMENTATION OF THE WAVEFRONT
	 *
	 * A while-loop goes through each pixel of the image and checks
	 * if the neighboring pixels in the directions UP, DOWN, LEFT and RIGHT.
	 *
	 * If the neighboring pixel is not obstacle (value less than 0), then the
	 * pixel-value is set to the number number of wave iterations, plus one.
	 * Thus, in the next wave it is the neighboring pixel, which neighboring pixels
	 * is being checked, and so on, until there is no pixels left to check.
	 *
	 */

	while (foundWave == true) // Look for next wave
	{
		foundWave = false;
		for (int y = 0; y < xWidth; y++)
		{
			for (int x = 0; x < xHeight; x++)
			{
				if (arr[x][y] == currentWave)
				{
					foundWave = true;
					xWave = x;
					yWave = y;

					//img.setPixel(y, x, currentWave/20);

					// Left direction
					if (xWave > 0) // Check if the robot hits an obstacle
						if (arr[xWave - 1][yWave] == 0) // Check if there is an obstacle
							arr[xWave - 1][yWave] = currentWave + 1; // Assign new value

					// A similar algorithm is repeated for each direction, so they are not commented.

					// Right direction
					if (xWave < (xHeight - 1))
						if (arr[xWave + 1][yWave] == 0)
							arr[xWave + 1][yWave] = currentWave + 1;

					// Down direction
					if (yWave > 0)
						if (arr[xWave][yWave - 1] == 0)
							arr[xWave][yWave - 1] = currentWave + 1;

					// Up direction
					if (yWave < (xWidth - 1))
						if (arr[xWave][yWave + 1] == 0)
							arr[xWave][yWave + 1] = currentWave + 1;
				}
			}
		}
		currentWave++; // Value for the next wave
	}
	return arr;
}

void offlineWaveFront::saveWavefront(){
	std::cout << "Saving image" << std::endl;
	int tmp = 0;
	for (int i = 0; i < xHeight; ++i)
	{
		for (int j = 0; j < xWidth; ++j)
		{
			tmp = img.getPixel(j,i);
			img.setPixel(j, i,tmp);
		}
	}
	img.saveImage("tmp2");
}

/*
int main() {

	offlineWaveFront offWavefront;

	// Initialize the wavefront map
	offWavefront.init();

	// Wavefront testing
	offWavefront.waveFront(100, 650);  // Block A, Room 1

	// Save image
	offWavefront.saveWavefront();
}
*/
