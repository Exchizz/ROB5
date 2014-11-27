//
//  structure.cpp
//  Coverage_planning
//
//  Created by Keerthikan Ratnarajah on 27/11/14.
//  Copyright (c) 2014 Keerthikan Ratnarajah. All rights reserved.
//

#include "structure.h"

void structure::priority_Blok_area(vector<square> rooms)
{
    int hits = 0;
    for (int i = 0  ; i<rooms.size(); i++)
    {
        
        if (abs(rooms[i].y4-rooms[i].y2)/abs((rooms[i].x3 - rooms[i].x1)) <= 22 and abs(rooms[i].y4-rooms[i].y2)/abs((rooms[i].x3 - rooms[i].x1)) >= 7) {
            cout << "detect" << endl;
            cout << endl;
            cout << rooms[i].x1 <<"," <<rooms[i].y1 << " " <<rooms[i].x2 <<"," <<rooms[i].y2 <<" "<< rooms[i].x3 <<"," <<rooms[i].y3<< " " << rooms[i].x4 <<"," <<rooms[i].y4 << endl;
            cout << endl;
            cout << endl;
            cout << endl;
            hits++;
        }
        
        
        
    }
    cout << hits << endl; 
    
};
//2611,1042 2611,107 2655,107 2655,1042
//2611,1042 2611,107 2655,107 2655,1042
//44/1976

