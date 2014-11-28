//
//  structure.cpp
//  Coverage_planning
//
//  Created by Keerthikan Ratnarajah on 27/11/14.
//  Copyright (c) 2014 Keerthikan Ratnarajah. All rights reserved.
//

#include "structure.h"


vector<square> structure::priority_Blok_area(vector<square> rooms)
{
    int hits = 0;
    vector<square> hallways;
    for (int i = 0  ; i<rooms.size(); i++)
    {
        
        if (abs(rooms[i].y4-rooms[i].y2)/abs((rooms[i].x3 - rooms[i].x1)) <= 22 and abs(rooms[i].y4-rooms[i].y2)/abs((rooms[i].x3 - rooms[i].x1)) >= 7) {
            cout << "hallways detect" << endl;
            cout << endl;
            cout << rooms[i].x1 <<"," <<rooms[i].y1 << " " <<rooms[i].x2 <<"," <<rooms[i].y2 <<" "<< rooms[i].x3 <<"," <<rooms[i].y3<< " " << rooms[i].x4 <<"," <<rooms[i].y4 << endl;
            cout << endl;
            cout << endl;
            cout << endl;
            hallways.push_back(rooms[i]);
            hits++;
        }
        
    }
    cout << hits << endl;

    return hallways;
};
void structure::Spiral( int X, int Y,Image &map){
    int x,y,dx,dy;
    x = y = dx =0;
    dy = -1;
    int t = std::max(X,Y);
    int maxI = t*t;
    for(int i =0; i < maxI; i++){
        if ((-X/2 <= x) && (x <= X/2) && (-Y/2 <= y) && (y <= Y/2)){
            map.setPixel(X, Y, WHITE);
        }
        if( (x == y) || ((x < 0) && (x == -y)) || ((x > 0) && (x == 1-y))){
            t = dx;
            dx = -dy;
            dy = t;
        }
        x += dx;
        y += dy;
    }
}

void structure::who_is_my_neighbour(Image &map,vector<pair<int, int>> hallways_center, vector<pair<int, int>> rooms)
{
    int hitA = 0;
    int hitB = 0;
    int hitC = 0;
    int hitD = 0;
    int hitE = 0;
    
    cout << hallways_center.size() << endl;

    for (int i = 0; i<rooms.size(); ++i) {
        cout << endl;
        cout << endl;
        cout << endl;
        cout << endl;
        cout << endl;
        cout << "looking at room "<<rooms[i].first<<"," <<rooms[i].second << endl;
        cout << endl;
        cout << endl;
        cout << endl;
        cout << endl;

        if (abs(hallways_center[0].first - rooms[i].first) < 130 and abs(hallways_center[0].second - rooms[i].second) < 600 )
        {
                //cout << "room in blok A found, center at " << hallways_center[0].first << ","<<hallways_center[0].second << endl;
            cout <<"room A " << i <<" "<< rooms[i].first<<"," <<rooms[i].second << endl;
            hitA++;
            blok_A.push(rooms[i]);
            map.setPixel(rooms[i].first, rooms[i].second, BLACK);
            cout << endl;
            cout << endl;
            cout << endl;
            cout << endl;
            cout << "SET" << endl; 
        }
        else{
            cout << "rejected room A because" << abs(hallways_center[0].first - rooms[i].first) << " " <<abs(hallways_center[0].second - rooms[i].second) << endl;

            
        }
        
        if (abs(hallways_center[1].first - rooms[i].first) < 150 and abs(hallways_center[1].second - rooms[i].second) < 600 ) {
                //cout << "room in blok B found, center at " <<hallways_center[1].first <<"," << hallways_center[1].second<< endl;
                cout<<"room B " << i << " " <<rooms[i].first<<"," <<rooms[i].second << endl;
            hitB++;
            blok_B.push(rooms[i]);
            map.setPixel(rooms[i].first, rooms[i].second, BLACK);
        }
        else
        {
            cout << "rejected room B because" << abs(hallways_center[1].first - rooms[i].first) << " " <<abs(hallways_center[1].second - rooms[i].second) << endl;
        }
        if (abs(hallways_center[2].first - rooms[i].first) < 150 and abs(hallways_center[2].second - rooms[i].second) < 600 ) {
               // cout << "room in blok C found, center at " << hallways_center[2].first << "," <<hallways_center[2].second << endl;
                cout<<"rooms C " <<i <<" "<< rooms[i].first<<"," <<rooms[i].second << endl;
            hitC++;
            blok_C.push(rooms[i]);
            map.setPixel(rooms[i].first, rooms[i].second, BLACK);

        }
        else{
            cout << "rejected room C because" << abs(hallways_center[2].first - rooms[i].first) << " " <<abs(hallways_center[2].second - rooms[i].second) << endl;
        }
        if (abs(hallways_center[3].first - rooms[i].first) < 160 and abs(hallways_center[3].second - rooms[i].second) < 900 ) {
                //cout << "room in blok D found, center at " << hallways_center[3].first << "," <<hallways_center[3].second << endl;
                cout<< "rooms D " <<i<<" "<< rooms[i].first<<"," <<rooms[i].second << endl;
            hitD++;
            blok_D.push(rooms[i]);
            map.setPixel(rooms[i].first, rooms[i].second, BLACK);

        }
        else{
            cout << "rejected room D because" << abs(hallways_center[3].first - rooms[i].first) << " " <<abs(hallways_center[3].second - rooms[i].second) << endl;
        }
        
        if (abs(hallways_center[4].first - rooms[i].first) < 130 and abs(hallways_center[4].second - rooms[i].second) < 600 ) {
                //cout << "room in blok E found, center at " << hallways_center[4].first << "," <<hallways_center[4].second << endl;
                cout <<"rooms E "<< i <<" "<< rooms[i].first<<"," <<rooms[i].second << endl;
            hitE++;
            blok_E.push(rooms[i]);
            map.setPixel(rooms[i].first, rooms[i].second, BLACK);

        }
        else{
            cout << "rejected room E because" << abs(hallways_center[4].first - rooms[i].first) << " " <<abs(hallways_center[4].second - rooms[i].second) << endl;
        }
    };
    for (int i = 0; i< blok_A.size(); ++i) {
        cout << "x,y: " << abs(blok_A.top().first - hallways_center[0].first) << "," << abs(blok_A.top().second- hallways_center[0].second) << endl;
        blok_A.pop();
    }
    cout << " "<<hitA <<" "<< hitB <<" "<< hitC <<" "<< hitD <<" " <<hitE << endl;
    
};
//2611,1042 2611,107 2655,107 2655,1042
//2611,1042 2611,107 2655,107 2655,1042
//44/1976

