/*
 * Image.cpp
 *
 *  Created on: Nov 7, 2014
 *      Author: exchizz
 */

#include "Image.h"

Image::Image(const std::string filename) {
	std::ofstream imageFile;
	imageFile.open(filename.c_str());
	if(imageFile.is_open()){
		std::cout << "Unable to open \"" + filename + "\"" << std::endl;
		exit(0);
	}

}

int Image::getWidth() {
	return width;
}

int Image::getHeight() {
	return height;
}
