//
//  main.cpp
//  Coverage_planning
//
//  Created by Keerthikan Ratnarajah on 03/11/14.
//  Copyright (c) 2014 Keerthikan Ratnarajah. All rights reserved.
//

#include <iostream>
#include "Image.h"
#include "Coverage.h"
#include <math.h>
#include <unistd.h>
using namespace std;

int main(int argc, const char * argv[]) {
    Image map;
    map.loadImage("/Users/keerthikanratnarajah/Documents/Kode/ROB5/src/Coverage/Coverage/Coverage_planning/Coverage_planning/complete_map_project.pgm");
    Image news;
    news.createImage("/Users/keerthikanratnarajah/Documents/Kode/ROB5/src/Coverage/Coverage/Coverage_planning/Coverage_planning/edge.pgm",  map.getWidth()-1, map.getHeight()-1);
    for (int x = 0; x < map.getWidth()-1 ; x++) {
        for (int y = 0; y < map.getHeight()-1; y++) {
            news.setPixel(x, y, sqrt(pow((map.getPixel(x, y+1) - map.getPixel(x, y)),2)+pow((map.getPixel(x+1, y) - map.getPixel(x, y)),2)));
        }
    }


    
    cout << "hello world" << endl;
    return 0;
}
