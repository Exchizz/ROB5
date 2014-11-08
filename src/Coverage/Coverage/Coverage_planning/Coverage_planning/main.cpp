//
//  main.cpp
//  Coverage_planning
//
//  Created by Keerthikan Ratnarajah on 03/11/14.
//  Copyright (c) 2014 Keerthikan Ratnarajah. All rights reserved.
//

#include <iostream>
#include "Filehandle.h"
#include "Coverage_planing.h"
#include <unistd.h>

int main(int argc, const char * argv[]) {
    
    Filehandle maps("/Users/keerthikanratnarajah/Documents/Kode/ROB5/src/Coverage/Coverage/Coverage_planning/Coverage_planning/complete_map_project.pgm");
    cout << maps.getHeight() << endl;
    cout << maps.getLenght() << endl;
    Coverage_planing test(maps);
    cout << "No way" << endl;
    std::cout << "Hello, World!\n";
    return 0;
}
