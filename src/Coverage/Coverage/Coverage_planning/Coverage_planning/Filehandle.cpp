//
//  Filehandle.cpp
//  Coverage_planning
//
//  Created by Keerthikan Ratnarajah on 03/11/14.
//  Copyright (c) 2014 Keerthikan Ratnarajah. All rights reserved.
//

#include "Filehandle.h"

Filehandle::Filehandle(string filename)
{

    ifstream map;
    map.open(filename,ios::binary);
    if (!map.is_open()) {
        cout << "An error occured while openning" << endl;
        exit(0);
    }
    
    
}