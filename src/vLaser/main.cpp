/*
 *	University of Southern Denmark
 *	Robotics in context
 *
 *	Project:		Distance Vector Computation
 *	Module name: 	main.cpp
 *
 *	Description:
 *
 *	------------------------------------------------------
 *	Change Log:
 *
 *	Date		ID		Change
 *	YYMMDD
 * 
 *	140908		NAL		Module Created
 *						Added initialization checks
 *	140909		NAL		Added Windows Console Attributes
 *	140916		NAL		Deleted Windows Console Attributes
 *						Updated for multiple OS
 *
 *	------------------------------------------------------
 */


/***************************** Include files *******************************/
#include <iostream>
#include <cmath>
#include <cstdlib>
#include "Image.hpp"
#include "PPMLoader.hpp"

/*****************************    Defines    *******************************/
#ifdef _WIN32
	#define windows 1;
#else
	#define windows 0;
#endif

int const upLeft		= 0;
int const upRight		= 1;
int const downLeft		= 2;
int const downRight		= 3;
int const vertical		= 4;
int const horisontal	= 5;

/*****************************   Constants   *******************************/

/*****************************   Functions   *******************************/


using namespace rw::sensor;
using namespace rw::loaders;

int determineDirection(int v, int u){
	int direction;
	if (v == 0 && u == 0)
		exit(-1);
	if (v < 0 && u > 0)
		direction = upLeft;
	if (v > 0 && u > 0)
		direction = upRight;
	if (v < 0 && u < 0)
		direction = downLeft;
	if (v > 0 && u < 0)
		direction = downRight;
	if (v == 0 && u != 0)
		direction = vertical;
	if (v != 0 && u == 0)
		direction = horisontal;

	return direction;
}

int main() {
	bool SystemPauseEnabled = windows;

	// Read argument
	std::string filename("Bane1.pgm");

	std::cout << "Loading image..." << std::endl;
	Image* img = PPMLoader::load(filename);

	int channel = 0; // allways 0 on grayscale image

	// 1. Initialization
		// 1.1 Read user input: Q_startX and Q_startY	
		int Q_startX;
		int Q_startY;
	
		std::cout << "\r\nPlease enter Q_start (x,y): ";
		std::cin >> Q_startX >> Q_startY;
		std::cout << std::endl;
		
		// (currentX and currentY is used for the current position of the robot)
		float currentX = Q_startX;
		float currentY = Q_startY;

		// 1.2 Check if Q_start is valid (start must lie inside picture and not in an obstacle)
		if (img->getPixelValuei(Q_startX, Q_startY, channel) == 0 || Q_startX > img->getWidth() || Q_startY > img->getWidth()){
			std::cout << "Error: ";
			std::cout << "Q_start is not valid! Exiting...\r\n" << std::endl;
			if(SystemPauseEnabled){
				system("pause");
			}
			exit(-1);
		}

		

		signed int vectorV[64] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 7, 6, 5, 4, 3, 2, 1, 0, -1, -2, -3, -4, -5, -6, -7, -8, -8, -8, -8, -8, -8, -8, -8, -8, -8, -8, -8, -8, -8, -8, -8, -8, -7, -6, -5, -4, -3, -2, -1 };
		signed int vectorU[64] = { 8, 8, 8, 8, 8, 8, 8, 8, 8, 7, 6, 5, 4, 3, 2, 1, 0, -1, -2, -3, -4, -5, -6, -7, -8, -8, -8, -8, -8, -8, -8, -8, -8, 8, 8, 8, 8, 8, 8, 8, 8, 7, 6, 5, 4, 3, 2, 1, 0, -1, -2, -3, -4, -5, -6, -7, -8, -8, -8, -8, -8, -8, -8, -8 };
		//signed int vectorV[3] = {0,1,1};
		//signed int vectorU[3] = {1,1,0};
		long int dist[64] = { 0 };
		
		// 1.4 Print image info
		std::cout << "\r\n-------------------------------------------------" << std::endl;
		std::cout << "Image: " << filename << " \r\nSize: " << img->getWidth() << "x" << img->getHeight() << " pixels" << std::endl;
		std::cout << "-------------------------------------------------" << std::endl;

		// 2. Loop	
		for (int i = 0; i < 64; i++){
			// 2.1 Calculate slope
			std::cout << std::endl;
			std::cout << i << "th iteration" << std::endl;
			float slope;
			float v = vectorV[i];
			float u = vectorU[i];
			std::cout << "vector(" << v << "," << u << ")" << std::endl;
			float currentX = Q_startX;
			float currentY = Q_startY;


			if (v == 0 || u == 0){
				slope = 0;
			}else{
				slope = float( std::abs(u) ) / float( std::abs (v) );
			}
			std::cout << "Slope: " << slope << "\r\n" << std::endl;
		
			// 1.6 Determine direction
			int direction = determineDirection(v,u);
			
			bool hitObstacle = false;
			
			while (!hitObstacle && (currentX < img->getWidth() && currentY < img->getHeight()) && (currentX > 0 && currentY > 0)){
				if (img->getPixelValuei(currentX, currentY, channel) == 255 || img->getPixelValuei(currentX, currentY, channel) == 20){
					img->setPixel8U(currentX, currentY, 20);
					
					switch (direction){
						case upLeft:
							currentX -= 1;
							currentY -= slope;
							break;
						case upRight:
							currentX += 1;
							currentY -= slope;
							break;
						case downLeft:
							currentX -= 1;
							currentY += slope;
							break;
						case downRight:
							currentX += 1;
							currentY += slope;
							break;
						case vertical:
							currentY -= (u / std::abs(u));
							break;
						case horisontal:
							currentX += (v / std::abs(v));
							break;
						default:
							break;
					}
				}else if (img->getPixelValuei(currentX, currentY, channel) == 0){
					// Indicate that we have hit an obstacle (terminates while loop)
					hitObstacle = true;		

					// Calculate the distance
					dist[i] = (sqrt(((currentX - Q_startX)*(currentX - Q_startX)) + ((currentY - Q_startY)*(currentY - Q_startY))));
					std::cout << "Distance from Q_start to obstacle: " << dist[i] << std::endl;
				}
			}
			if (currentX >= img->getWidth() || currentX < 0 || currentY >= img->getHeight() || currentY < 0){
				//std::cout << "Leaving image... No obstacles was found in the vectors direction.\r\n" << std::endl;
				dist[i] = 0;
			}
		}

		
		

	std::cout << "Saving image..." << std::endl;
	std::cout << std::endl;
	// save image
	img->saveAsPGM("testout.pgm");

	// cleanup
	delete img;

	if(SystemPauseEnabled){
		system("pause");
	}
	return 0;
}


//test
