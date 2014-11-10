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
#include <unistd.h>
using namespace std;

int main(int argc, const char * argv[]) {
    Image map;
    map.loadImage("/Users/keerthikanratnarajah/Documents/Kode/ROB5/src/Coverage/Coverage/Coverage_planning/Coverage_planning/complete_map_project.pgm");
    Coverage routing(map);
    return 0;
}
