////
////  structure.cpp
////  Coverage_planning
////
////  Created by Keerthikan Ratnarajah on 27/11/14.
////  Copyright (c) 2014 Keerthikan Ratnarajah. All rights reserved.
////
//
//#include "structure.h"
//
//Room::Room(square &Lokale) :  corners(Lokale.x1,Lokale.y1,Lokale.x2,Lokale.y2,Lokale.x3,Lokale.y3,Lokale.x4,Lokale.y4)
//
//{
//    int diffX = std::max(Lokale.x1, Lokale.x4) - std::min(Lokale.x1, Lokale.x4);
//    int diffY = std::max(Lokale.y1, Lokale.y2) - std::min(Lokale.y1, Lokale.y2);
//    center.first = (diffX/2) + std::min(Lokale.x1, Lokale.x4);
//    center.second = (diffY/2) + std::min(Lokale.y1, Lokale.y2);
//    distance = 0;
//    
//    
//}
//
//vector<Room> structure::priority_Blok_area(vector<square> rooms)
//{
//    int hits = 0;
//    vector<Room> hallways;
//    cout << rooms.size() << endl;
//    for (int i = 0  ; i<rooms.size(); i++)
//    {
//        Lokale.push_back(Room(rooms[i]));
//        if (abs(rooms[i].y4-rooms[i].y2)/abs((rooms[i].x3 - rooms[i].x1)) <= 22 and abs(rooms[i].y4-rooms[i].y2)/abs((rooms[i].x3 - rooms[i].x1)) >= 7) {
//            hallways.push_back(Room(rooms[i]));
//            hits++;
//        }
//        //detection of hall in the middle
//        if (rooms[i].x2 == 969 and rooms[i].y2 == 1136 and rooms[i].x3 == 3755) {
//            hallways.push_back(Room(rooms[i]));
//            hits++;
//
//        }
//    }
//    return hallways;
//};
//
//void structure::who_is_my_neighbour(Image &img,vector<Room> hallways_center)
//{
//    vector<int> samlet;
//    int j = 10000000;
//    int iterator = 0;
//    
//
//    
//    for (int i = 0; i < Lokale.size(); ++i) {
//        cout << i << endl;
//        samlet.push_back((abs(hallways_center[0].center.first - Lokale[i].center.first) + abs(hallways_center[0].center.second - Lokale[i].center.second)));
//        samlet.push_back(abs(hallways_center[1].center.first -  Lokale[i].center.first) + abs(hallways_center[1].center.second - Lokale[i].center.second));
//        samlet.push_back(abs(hallways_center[2].center.first -  Lokale[i].center.first) + abs(hallways_center[2].center.second - Lokale[i].center.second));
//        samlet.push_back(abs(hallways_center[3].center.first -  Lokale[i].center.first) + abs(hallways_center[3].center.second - Lokale[i].center.second));
//        samlet.push_back(abs(hallways_center[4].center.first -  Lokale[i].center.first) + abs(hallways_center[4].center.second - Lokale[i].center.second));
//        samlet.push_back(abs(hallways_center[5].center.first -  Lokale[i].center.first) + abs(hallways_center[5].center.second - Lokale[i].center.second));
//        if (Lokale[i].center.first > 4000) {
//            
//        cout <<i<< "if D" << abs(hallways_center[4].center.first -  Lokale[i].center.first) + abs(hallways_center[4].center.second - Lokale[i].center.second) << endl;
//         cout << "if E" << abs(hallways_center[5].center.first -  Lokale[i].center.first) + abs(hallways_center[5].center.second - Lokale[i].center.second) << endl;
//        
//        }
//        
//        for (int k = 0; k <= 5; ++k) {
//            if (samlet[k] < j) {
//                iterator = k;
//                j = samlet[k];
//            }
//        }
//        
//        switch (iterator) {
//            case BLOK_A:
//                cout << "lies in A" << endl;
//                Lokale[i].distance = samlet[iterator];
//                iterator = 0;
//                j = 10000000;
//                img.setPixel(Lokale[i].center.first, Lokale[i].center.second, BLACK);
//                blok_A.push(Lokale[i]);
//                samlet.clear();
//            break;
//            case BIG_HALL:
//                cout << "lies in Bighall" << endl;
//                Lokale[i].distance = samlet[iterator];
//                iterator = 0;
//                j = 10000000;
//                img.setPixel(Lokale[i].center.first, Lokale[i].center.second, BLACK);
//                Big_hall.push(Lokale[i]);
//                samlet.clear();
//            break;
//            case BLOK_B:
//                cout << "lies in B" << endl;
//                Lokale[i].distance = samlet[iterator];
//                iterator = 0;
//                j = 10000000;
//                img.setPixel(Lokale[i].center.first, Lokale[i].center.second, BLACK);
//                blok_B.push(Lokale[i]);
//                samlet.clear();
//            break;
//            case BLOK_C:
//                cout << "lies in C" << endl;
//                Lokale[i].distance = samlet[iterator];
//                iterator = 0;
//                j = 10000000;
//                img.setPixel(Lokale[i].center.first, Lokale[i].center.second, BLACK);
//                blok_C.push(Lokale[i]);
//                samlet.clear();
//            break;
//            case BLOK_D:
//                cout << "lies in D" << endl;
//                cout << Lokale[i].center.first << "," << Lokale[i].center.first << endl;
//                Lokale[i].distance = samlet[iterator];
//                iterator = 0;
//                j = 10000000;
//                img.setPixel(Lokale[i].center.first, Lokale[i].center.second, BLACK);
//                blok_D.push(Lokale[i]);
//                samlet.clear();
//            break;
//            case BLOK_E:
//                cout << "lies in E" << endl;
//                Lokale[i].distance = samlet[iterator];
//                iterator = 0;
//                j = 10000000;
//                img.setPixel(Lokale[i].center.first, Lokale[i].center.second, BLACK);
//                blok_E.push(Lokale[i]);
//                samlet.clear();
//            break;
//       
//        
//        };
//     
//    };
//    
//    
//    for (int i = 0; i < blok_A.size(); ++i) {
//        cout <<blok_A.top().distance <<endl;
//        blok_A.pop();
//    }
//
//    
//};
//
