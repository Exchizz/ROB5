//============================================================================
// Name        : Wavefront_online.cpp
// Author      : jejep12
// Version     : v2
// Description : Wavefront: online version
//============================================================================
#ifndef ONLINEWAVEFRONT_H_
#define ONLINEWAVEFRONT_H_

#include <iostream>
#include <fstream>
#include <math.h>
#include "Image.h"
#include "iomanip"

class onlineWaveFront{
private:
	Image img;
	Image imgcopy;
	int incValue;
	int listsize;
	int listsize2;
	int xHeight;
	int xWidth;
public:
	onlineWaveFront::onlineWaveFront(Image &tempImg);
	void makeWaveFront(int,int,int,int);
};

#endif /* ONLINEWAVEFRONT_H_ */

