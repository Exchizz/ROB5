//
//  Coverage.cpp
//  Coverage_planning
//
//  Created by Keerthikan Ratnarajah on 10/11/14.
//  Copyright (c) 2014 Keerthikan Ratnarajah. All rights reserved.
//

#include "Coverage.h"

Coverage::Coverage( Image& map)
{
   // int x_temp;
   // int y_temp;
//    
//    vector<vector<pair<int,int>>> tempPixelList (map.getWidth(), vector<pair<int, int>>(map.getHeight()));
//    vector<vector<Cell>> cell_Objects (map.getWidth(),vector<Cell>(map.getHeight()));
//    
//    //Each free pixel gets celled
//    for (int x = 0; x<map.getWidth(); ++x) {
//        cout << "beta" << endl;
//        for (int y = 0; y<map.getHeight(); ++y) {
//            if(map.getPixel(x,y) == 255)
//            {
//                cout << x << y << endl; 
//                tempPixelList[x][y] = make_pair(x, y);
//                cell_Objects[x].push_back(Cell(tempPixelList));
//                cout << tempPixelList[x][y].second << endl;
//                map.setPixel(tempPixelList[x][y].first,tempPixelList[x][y].second,100);
//                cout << "map" << endl;
//            };
//            
//        };
//    };
//  
//
//    int j = 0;
//        for (int i = 1; i<=1180; ++i) {
//            //cout << cell_Objects[i].pixels[0].second - cell_Objects[i-1].pixels[0].second  << " i: " << i << endl;
//            //cout << "ROW er!!!! " << j << endl;
//            //cout << "reel y pixel " << 1180*(j+1) - i << endl;
//            if (cell_Objects[i].pixels[0].second - cell_Objects[i-1].pixels[0].second == 1)
//            {
//                cell_Objects[j].merge(cell_Objects[i]);
//                cell_Objects.insert(cell_Objects.begin()+j+1,cell_Objects.begin()+i+1 , cell_Objects.end());
//            }
//            else if(i == 1180 && j< map.getWidth()){
//              //  cout << "next row" << endl;
//                j++;
//                i = 0;
//                i = j+i;
//            }
//            else
//                cell_Objects.erase(cell_Objects.begin()+i, cell_Objects.end());
//            
//        }
//    cout << "merged" << endl;
    

};
    
