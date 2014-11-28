/*
 * onlineWaveFront.h
 *
 *  Created on: Nov 28, 2014
 *      Author: jes
 */

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
    int incValue=2;
	int listsize = 0;
	int listsize2 = 1;
	int xHeight;
	int xWidth;
public:
	onlineWaveFront();
	void makeWaveFront(int,int,int,int);
	~onlineWaveFront();
};

#endif /* ONLINEWAVEFRONT_H_ */
