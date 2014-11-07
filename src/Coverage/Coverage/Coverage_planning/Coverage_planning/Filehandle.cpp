//
//  Filehandle.cpp
//  Coverage_planning
//
//  Created by Keerthikan Ratnarajah on 03/11/14.
//  Copyright (c) 2014 Keerthikan Ratnarajah. All rights reserved.
//

#include "Filehandle.h"

Filehandle::Filehandle(string filename){

    map.open(filename,ios::binary);
    if (!map.is_open()) {
        cout << "An error occured while openning" << endl;
        exit(0);
    }
}

int Filehandle::getHeight(){
    int height;
    long long temp_position = map.tellg();
    map.seekg(42,map.beg);
    map >> height;
    map.seekg(temp_position,map.beg);
    return height;
    
};

int Filehandle::getLenght(){
    int lenght;
    long long temp_position = map.tellg();
    map.seekg(42,map.beg);
    map >> lenght >> lenght;
    map.seekg(temp_position,map.beg);
    return lenght;
};