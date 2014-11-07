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
class Image{
public:
	Image(std::string filename);
	int getWidth();
	int getHeight();

private:
	std::vector< std::vector<int> > imageData;
	int width;
	int height;
};

#endif /* IMAGE_H_ */
