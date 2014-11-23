//
//  Cell.cpp
//  Coverage_planning
//
//  Created by Keerthikan Ratnarajah on 14/11/14.
//  Copyright (c) 2014 Keerthikan Ratnarajah. All rights reserved.
//

#include "Cell.h"  
Cell::Cell( vector<pair<int, int>> &cell_temp){
    pixels = move(cell_temp);
    visited = false;
    cleaned = false;
    
};

void Cell::merge(Cell &B){
    
    pixels.insert(pixels.end(),B.pixels.begin(),B.pixels.end());
};
