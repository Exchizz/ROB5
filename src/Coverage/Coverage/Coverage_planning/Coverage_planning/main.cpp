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
#include "planning.h"
#include "structure.h"

using namespace std;

int main(int argc, const char * argv[]) {
    Planning img;
    img.loadImage("/Users/keerthikanratnarajah/Documents/Kode/ROB5/src/Coverage/ROB5-master/img/complete_map_project.pgm");

    auto rooms = img.detect_rooms();
    auto hallways = img.Big_rooms(rooms);
    img.who_is_my_neighbour(hallways);
    img.saveImage("/Users/keerthikanratnarajah/Documents/Kode/ROB5/src/Coverage/Coverage/Coverage_planning/Coverage_planning/edge.pgm");
    
    cout << "hello world" << endl;
    return 0;
}
