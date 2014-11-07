//
//  Filehandle.h
//  Coverage_planning
//
//  Created by Keerthikan Ratnarajah on 03/11/14.
//  Copyright (c) 2014 Keerthikan Ratnarajah. All rights reserved.
//
#pragma once
#ifndef Coverage_planning_Filehandle_h
#define Coverage_planning_Filehandle_h 
#include <iostream>
#include <string>
#include <fstream>
#endif


using namespace std;

class Filehandle{
public:
    Filehandle(string filename);
    int getHeight();
    int getLenght();
    ifstream map;
private:
    
};