//
//  Coverage.h
//  Coverage_planning
//
//  Created by Keerthikan Ratnarajah on 10/11/14.
//  Copyright (c) 2014 Keerthikan Ratnarajah. All rights reserved.
//

#ifndef __Coverage_planning__Coverage__
#define __Coverage_planning__Coverage__

#include <stdio.h>
#include <iostream>
#include <list>
#include "Image.h"
using namespace std;
class Coverage{
public:
    Coverage(const Image&);
    list<int> tempUpperbound;
    list<int> tempLowerbound;
private:
    
};

#endif /* defined(__Coverage_planning__Coverage__) */
