//
//  structure.cpp
//  Coverage_planning
//
//  Created by Keerthikan Ratnarajah on 27/11/14.
//  Copyright (c) 2014 Keerthikan Ratnarajah. All rights reserved.
//

#include "structure.h"

Room::Room(square &Lokale) :  corners(Lokale.x1,Lokale.y1,Lokale.x2,Lokale.y2,Lokale.x3,Lokale.y3,Lokale.x4,Lokale.y4)

{
    int diffX = std::max(Lokale.x1, Lokale.x4) - std::min(Lokale.x1, Lokale.x4);
    int diffY = std::max(Lokale.y1, Lokale.y2) - std::min(Lokale.y1, Lokale.y2);
    center.first = (diffX/2) + std::min(Lokale.x1, Lokale.x4);
    center.second = (diffY/2) + std::min(Lokale.y1, Lokale.y2);
    distance = 0;
    
    
}

vector<Room> structure::priority_Blok_area(vector<square> rooms)
{
    int hits = 0;
    vector<Room> hallways;
    cout << rooms.size() << endl;
    for (int i = 0  ; i<rooms.size(); i++)
    {
        Lokale.push_back(Room(rooms[i]));
        if (abs(rooms[i].y4-rooms[i].y2)/abs((rooms[i].x3 - rooms[i].x1)) <= 22 and abs(rooms[i].y4-rooms[i].y2)/abs((rooms[i].x3 - rooms[i].x1)) >= 7) {
            cout << "hallways detect" << endl;
            cout << endl;
            cout << rooms[i].x1 <<"," <<rooms[i].y1 << " " <<rooms[i].x2 <<"," <<rooms[i].y2 <<" "<< rooms[i].x3 <<"," <<rooms[i].y3<< " " << rooms[i].x4 <<"," <<rooms[i].y4 << endl;
            cout << endl;
            cout << endl;
            cout << endl;
            hallways.push_back(Room(rooms[i]));
            hits++;
        }
        //detection of hall in the middle
        if (rooms[i].x2 == 969 and rooms[i].y2 == 1136 and rooms[i].x3 == 3755) {
            //cout << rooms[i].x1 << "," << rooms[i].y1 << " and " << rooms[i].x2 << "," << rooms[i].y2 << " and " << rooms[i].x3 <<","<< rooms[i].y3 << " and "  << rooms[i].x4 << "," << rooms[i].y4
            //<< endl;
            //first = double(abs(rooms[i].y4-rooms[i].y2))/double(abs(rooms[i].x3 - rooms[i].x1));
            //second =double(abs(rooms[i].y4-rooms[i].y2))/double(abs((rooms[i].x3 - rooms[i].x1)));
            //cout << "Første forhold: " << (rooms[i].y4-rooms[i].y2) << " "<< (rooms[i].x3 - rooms[i].x1) << " " << first << endl;
            //cout << "andet forhold: " << (rooms[i].y4-rooms[i].y2) <<" "<< (rooms[i].x3 - rooms[i].x1) << " " <<second << endl;
            hallways.push_back(Room(rooms[i]));
            hits++;

        }
    }
    cout << "Done------------------------------------------" << endl; 
    cout << hits << endl;
    //969 , 1137
    // Returns Corner vector of all squares which define the hallways.
    return hallways;
};

void structure::who_is_my_neighbour(Image &img,vector<Room> hallways_center)
{
    int hitA = 0;
    int hitB = 0;
    int hitBig= 0;
    int hitC = 0;
    int hitD = 0;
    int hitE = 0;
    vector<int> samlet;
    int j = 10000000;
    int iterator = 0;
    cout << "--------------------------------------------------------" << endl;
    cout << "hallways_center: " << hallways_center.size() << endl;
    
    
    for (int i = 0 ; i<hallways_center.size(); ++i) {
        cout << "Centers " <<hallways_center[i].center.first << "," << hallways_center[i].center.second  << endl;
    }

//    exit(0);
    
    for (int i = 0; i < Lokale.size(); ++i) {
        cout << i << endl;
        samlet.push_back((abs(hallways_center[0].center.first - Lokale[i].center.first) + abs(hallways_center[0].center.second - Lokale[i].center.second)));
        samlet.push_back(abs(hallways_center[1].center.first -  Lokale[i].center.first) + abs(hallways_center[1].center.second - Lokale[i].center.second));
        samlet.push_back(abs(hallways_center[2].center.first -  Lokale[i].center.first) + abs(hallways_center[2].center.second - Lokale[i].center.second));
        samlet.push_back(abs(hallways_center[3].center.first -  Lokale[i].center.first) + abs(hallways_center[3].center.second - Lokale[i].center.second));
        samlet.push_back(abs(hallways_center[4].center.first -  Lokale[i].center.first) + abs(hallways_center[4].center.second - Lokale[i].center.second));
        samlet.push_back(abs(hallways_center[5].center.first -  Lokale[i].center.first) + abs(hallways_center[5].center.second - Lokale[i].center.second));
        if (Lokale[i].center.first > 4000) {
            
        cout <<i<< "if D" << abs(hallways_center[4].center.first -  Lokale[i].center.first) + abs(hallways_center[4].center.second - Lokale[i].center.second) << endl;
         cout << "if E" << abs(hallways_center[5].center.first -  Lokale[i].center.first) + abs(hallways_center[5].center.second - Lokale[i].center.second) << endl;
        
        }
        
        for (int k = 0; k <= 5; ++k) {
            if (samlet[k] < j) {
                iterator = k;
                j = samlet[k];
            }
        }
        
        
        
        if (iterator == 0) {
            cout << "lies in A" << endl;
            Lokale[i].distance = samlet[iterator];
            iterator = 0;
            j = 10000000;
            hitA++;
            img.setPixel(Lokale[i].center.first, Lokale[i].center.second, BLACK);
            blok_A.push(Lokale[i]);
            samlet.clear();
        }
        if (iterator == 1) {
            cout << "lies in Bighall" << endl;
            Lokale[i].distance = samlet[iterator];
            iterator = 0;
            j = 10000000;
            hitBig++;
            img.setPixel(Lokale[i].center.first, Lokale[i].center.second, BLACK);
            Big_hall.push(Lokale[i]);
            samlet.clear();


        }
        if (iterator == 2) {
            cout << "lies in B" << endl;
            Lokale[i].distance = samlet[iterator];
            iterator = 0;
            j = 10000000;
            hitB++;
            img.setPixel(Lokale[i].center.first, Lokale[i].center.second, BLACK);
            blok_B.push(Lokale[i]);
            samlet.clear();

        }
        if (iterator == 3) {
            cout << "lies in C" << endl;
            Lokale[i].distance = samlet[iterator];
            iterator = 0;
            j = 10000000;
            hitC++;
            img.setPixel(Lokale[i].center.first, Lokale[i].center.second, BLACK);
            blok_C.push(Lokale[i]);
            samlet.clear();

        }
        if (iterator == 4) {
            cout << "lies in D" << endl;
            cout << Lokale[i].center.first << "," << Lokale[i].center.first << endl;
            Lokale[i].distance = samlet[iterator];
            iterator = 0;
            j = 10000000;
            hitD++;
            img.setPixel(Lokale[i].center.first, Lokale[i].center.second, BLACK);
            blok_D.push(Lokale[i]);
            samlet.clear();


        }
        if (iterator == 5) {
            cout << "lies in E" << endl;
            Lokale[i].distance = samlet[iterator];
            iterator = 0;
            j = 10000000;
            hitE++;
            img.setPixel(Lokale[i].center.first, Lokale[i].center.second, BLACK);
            blok_E.push(Lokale[i]);
            samlet.clear();
        }
        
    };
    

    cout << " "<<hitA <<" "<<hitBig<<" "<< hitB <<" "<< hitC <<" "<< hitD <<" " <<hitE << endl;
    
};
//2611,1042 2611,107 2655,107 2655,1042
//2611,1042 2611,107 2655,107 2655,1042
//44/1976

