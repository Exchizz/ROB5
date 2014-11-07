//
//  main.cpp
//  Coverage_planning
//
//  Created by Keerthikan Ratnarajah on 03/11/14.
//  Copyright (c) 2014 Keerthikan Ratnarajah. All rights reserved.
//

#include <iostream>
#include "Filehandle.h"
#include <unistd.h>

int main(int argc, const char * argv[]) {
    
    Filehandle map("/Users/keerthikanratnarajah/Documents/Kode/ROB5/src/Coverage/Coverage/Coverage_planning/Coverage_planning/complete_map_project.pgm");
    
    cout << map.getHeight() << endl;
    cout << map.getLenght() << endl;
    
    
    std::cout << "Hello, World!\n";
    return 0;
}
