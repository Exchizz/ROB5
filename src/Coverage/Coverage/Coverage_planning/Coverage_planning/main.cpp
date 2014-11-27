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
    structure billede;
    img.loadImage("/Users/keerthikanratnarajah/Documents/Kode/ROB5/src/Coverage/Coverage/Coverage_planning/complete_map_project.pgm");
    img.detect_rooms();
    billede.priority_Blok_area(img.detect_rooms()); 
    //img.saveImage("/Users/keerthikanratnarajah/Documents/Kode/ROB5/src/Coverage/Coverage/Coverage_planning/Coverage_planning/edge.pgm");
    
    cout << "hello world" << endl;
    return 0;
}
