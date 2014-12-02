/*
 * wavefront_online.h
 *
 *  Created on: Dec 1, 2014
 *      Author: jes
 */

#ifndef WAVEFRONT_ONLINE_H_
#define WAVEFRONT_ONLINE_H_


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
	onlineWaveFront();
	void makeWaveFront(int,int,int,int);
	~onlineWaveFront();
};


#endif /* WAVEFRONT_ONLINE_H_ */
