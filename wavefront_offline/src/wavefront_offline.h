/*
 * wavefront_offline.h
 *
 *  Created on: Dec 1, 2014
 *      Author: jes
 */

#ifndef WAVEFRONT_OFFLINE_H_
#define WAVEFRONT_OFFLINE_H_


#include <iostream>
#include <vector>
#include <list>
#include <fstream>
#include "Image.h"

class offlineWaveFront{
private:

public:
	Image img;
	
	int **arr;

	int xHeight;
	int xWidth;

	offlineWaveFront();
	int** waveFront(int,int);
	int** init();
	void saveWavefront();
	~offlineWaveFront();
};


#endif /* WAVEFRONT_OFFLINE_H_ */
