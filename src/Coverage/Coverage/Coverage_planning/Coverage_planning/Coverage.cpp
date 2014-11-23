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
    vector<pair<int, int>> tempPixelList;
   // int x_temp;
   // int y_temp;
    vector<Cell> cell_Objects;
    for (int x = 0; x<map.getWidth(); ++x) {
        for (int y = 0; y<map.getHeight(); ++y) {
            if(map.getPixel(x,y) == 255)
            {
                tempPixelList.push_back(make_pair(x,y));
                map.setPixel(x, y, 100);
                cell_Objects.push_back(Cell(tempPixelList));
                tempPixelList.clear();
            };
            
        };
    };
    for(int j = 0; j< 30000; ++j) {
        int i = j;
            while(map.getPixel(cell_Objects[j].pixels[0].first,cell_Objects[j].pixels[0].second) == 100 && j < 30000)
            {
                cout << "merge possible " << map.getPixel(cell_Objects[i].pixels[0].first, cell_Objects[i].pixels[0].second) << " koordinater " << cell_Objects[i].pixels[0].first<< "," << cell_Objects[i].pixels[0].second << " and " << map.getPixel(cell_Objects[j].pixels[0].first, cell_Objects[j].pixels[0].second) << " koordinater "<<cell_Objects[j].pixels[0].first << ","<<  cell_Objects[j].pixels[0].second << endl;
                cell_Objects[i].merge(cell_Objects[j]);
                cout << cell_Objects[i].pixels.size() << endl;
                cout << "merged" << endl;
                ++j;
            }
    }
    
    for (int i = 0; i < cell_Objects[0].pixels.size(); ++i) {
        cout << "pixel positions x: " << cell_Objects[0].pixels[i].first << " y: " <<  cell_Objects[0].pixels[i].second << endl;
        map.setPixel(cell_Objects[0].pixels[i].first, cell_Objects[0].pixels[i].second, 0);
    }
    
    
};
    
