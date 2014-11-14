/*
 * Image.h
 *
 *  Created on: Nov 7, 2014
 *      Author: exchizz
 */

#ifndef IMAGE_H_
#define IMAGE_H_


#include <vector>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <sstream>
#include <algorithm>    // std::reverse
class Image{
public:
	Image();
	int getWidth();
	int getHeight();
	int getMaxValue();
	std::string getVersion();
	int getPixel(int width, int height);

	void setPixel(const int width, const int height, const int value);

	void createVector(std::vector< std::vector <int> >  &image);
	void loadImage(const std::string filename);
	void saveImage(std::string filename);

private:
	std::fstream imageFile;
	int width;
	int height;
	int maxValue;
    std::vector< std::vector<int> > imageData;
	std::string inputLine;
	std::string version;
	std::stringstream ss;
<<<<<<< HEAD:src/Coverage/Coverage/Coverage_planning/Coverage_planning/Image.h
	bool createFile;
=======
>>>>>>> origin/Mathias:src/Image.h
};

#endif /* IMAGE_H_ */
