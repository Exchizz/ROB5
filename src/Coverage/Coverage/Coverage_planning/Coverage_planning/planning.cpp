/*
 *	University of Southern Denmark
 *	Robotics in context
 *
 *	Project:		ROB5 - Cup Collector
 *	Module name:	planning.cpp
 *
 *	Description:
 *
 *	------------------------------------------------------
 *	Change Log:
 *
 *	Date		ID		Change
 *	YYMMDD
 *
 *	141123		NAL		Module Created
 *	141126		NAL		Cleaned code
 *						Added comments
 *
 *	------------------------------------------------------
 */

/***************************** Include files *******************************/
#include <iostream>
#include "image.h"
#include "planning.h"

/*****************************    Defines    *******************************/

/*****************************   Constants   *******************************/

/*****************************   Functions   *******************************/



square::square(){
    
    x1 = 0;
    x2 = 0;
    x3 = 0;
    x4 = 0;
    y1 = 0;
    y2 = 0;
    y3 = 0;
    y4 = 0;
    
}

Room::Room(square &Lokale) :  corners(Lokale.x1,Lokale.y1,Lokale.x2,Lokale.y2,Lokale.x3,Lokale.y3,Lokale.x4,Lokale.y4)
{
    int diffX = std::max(Lokale.x1, Lokale.x4) - std::min(Lokale.x1, Lokale.x4);
    int diffY = std::max(Lokale.y1, Lokale.y2) - std::min(Lokale.y1, Lokale.y2);
    center.first = (diffX/2) + std::min(Lokale.x1, Lokale.x4);
    center.second = (diffY/2) + std::min(Lokale.y1, Lokale.y2);
    distance = 0;
    
    
};

std::vector<Room> Planning::priority_Blok_area(std::vector<square> rooms){

    std::vector<Room> hallways;
    for (int i = 0  ; i<rooms.size(); i++)
    {
        Lokale.push_back(Room(rooms[i]));
        if (abs(rooms[i].y4-rooms[i].y2)/abs((rooms[i].x3 - rooms[i].x1)) <= 22 and abs(rooms[i].y4-rooms[i].y2)/abs((rooms[i].x3 - rooms[i].x1)) >= 7) {
            std::cout << "hallway" << std::endl;
            hallways.push_back(Room(rooms[i]));
        }
        //detection of hall in the middle
        if (rooms[i].x2 == 969 and rooms[i].y2 == 1136 and rooms[i].x3 == 3755) {
            std::cout << "hallway" << std::endl;
            hallways.push_back(Room(rooms[i]));
        }
    }
    return hallways;
    
};

bool Planning::is_black(int x, int y) {
    if (x >= this->getWidth()) {
        std::cout << "Error: Width out of range\n";
        return false;
    }
    if (y >= this->getHeight()) {
        std::cout << "Error: Height out of range\n";
        return false;
    }
    if (this->getPixel(x, y) == BLACK)
        return true;
    else
        return false;
}

void Planning::draw_area(square temp) {
    //DEBUG: Print minimum and maximum values for coordinates (x,y)
    std::cout << std::endl;
    std::cout << "x: " << std::min(temp.x1, temp.x4) << "," << std::max(temp.x1, temp.x4) << std::endl;
    std::cout << "y: " << std::min(temp.y1, temp.y2) << "," << std::max(temp.y1, temp.y2) << std::endl;
    
    
    for (int x = std::min(temp.x1, temp.x4); x < std::max(temp.x1, temp.x4)+1;x++) {
        for (int y = std::min(temp.y1, temp.y2); y < std::max(temp.y1, temp.y2)+1;y++) {
            if (state == 0)
                setPixel(x, y, 50);
            else if (state == 1)
                setPixel(x, y, 100);
            else if (state == 2)
                setPixel(x, y, 150);
            else if (state == 3)
                setPixel(x, y, 200);
        }
    }
    state++;
    if (state > 3)
        state = 0;
}

/*
 * 1. Detects all upper left corners of squares, then
 * 2. it detects the upper right and then the lower left corner.
 * 3. Finally it "computes" the last corner and stores them in a
 * data type called square (which contains a pair of coordinates to each corner)
 */
std::vector<square> Planning::detect_rooms() {
    std::pair<int, int> corner;
    std::vector<std::pair<int, int>> listCorners;
    
    //1. Find all upper left corners
    for (int x = 0; x < getWidth(); x++) {
        for (int y = 0; y < getHeight(); y++) {
            if (is_black(x, y) and is_black(x + 1, y) and is_black(x + 2, y) and is_black(x, y - 1) and is_black(x, y - 2) and not is_black(x + 1, y - 1)) {
                // Upper left corner found
                corner = std::make_pair(x + 1, y - 1);
                // Push pair of coordinates of the corner onto vector
                listCorners.push_back(corner);
            }
        }
    }
    
    // 2. Loop through list of upper left corners and find remaining matching corners
    for (auto it = listCorners.begin(); it != listCorners.end(); ++it) {
        // 2.1 Initialize starting points
        std::pair<int, int> temp_corner = *it;
        int xLU = temp_corner.first + 1;
        int yLU = temp_corner.second - 1;
        int xRU = temp_corner.first + 1;
        int yLD = temp_corner.second - 1;
        bool outSideBox = false;
        
        // 2.2 	Detect upper right corner
        // 		Move horizontally right from (x+1,y-1) to first black pixel
        while (!is_black(xRU, yLU) and !outSideBox) {
            // 2.2.1 Check that we're still inside the image
            if (xRU >= getWidth()) {
                outSideBox = true;
                break;
            }
            xRU++;
        }
        // 2.3 	Detect lower left corner
        // 		Move vertically downwards from (x+1,y-1) to first black pixel
        while (!is_black(xLU, yLD) and !outSideBox) {
            // 2.3.1 Check that we're still inside the image
            if (yLD <= 0) {
                outSideBox = true;
                break;
            }
            yLD--;
        }
        
        
        // 2.4 Store coordinates of square in a vector
        if (!outSideBox) {
            // 2.4.1 Check that there's minimum 4 pixels between corners
            if (std::abs(yLU - yLD) > 4 and std::abs(xLU - xRU) > 4) {
                // constructor of square receives: (x1,y1,x2,y2,x3,y3,x4,y4)
                listSquares.emplace_back(xLU - 1, yLU + 1, xLU - 1, yLD + 1, xRU - 1, yLD + 1, xRU - 1, yLU + 1);
                
                /*
                 * emplace_back() invokes the constructor related to the type of the vector,
                 * in this case <squares>. This means that the object is created directly in
                 * the vector rather than creating it and then pushing onto the list.
                 */
                
                // DEBUG: Print coordinates
                std::cout << std::endl;
                std::cout << "Corner LU: (" << xLU-1 << "," << yLU+1 << ")\n";
                std::cout << "Corner RU: (" << xRU-1 << "," << yLU+1 << ")\n";
                std::cout << "Corner LD: (" << xRU-1 << "," << yLD+1 << ")\n";
                std::cout << "Corner RD: (" << xLU-1 << "," << yLD+1 << ")\n";
                
                // DEBUG: Color each corner
                setPixel(xLU - 1, yLU + 1, 100);
                setPixel(xRU - 1, yLU + 1, 100);
                setPixel(xRU - 1, yLD + 1, 100);
                setPixel(xLU - 1, yLD + 1, 100);
            }
        }
    }
    //DEBUG: Draw squares' area
    for (auto square : listSquares) {
        draw_area(square);
    }
    
    //
    return listSquares;
}

std::vector<std::pair<int,int>> Planning::detect_center(std::vector<square> listSquares){
    std::pair<int,int> center;
    std::vector<std::pair<int,int>> listCenters;
    
    for(auto square : listSquares){
        int diffX = std::max(square.x1, square.x4) - std::min(square.x1, square.x4);
        int diffY = std::max(square.y1, square.y2) - std::min(square.y1, square.y2);
        
        center.first = (diffX/2) + std::min(square.x1, square.x4);
        center.second = (diffY/2) + std::min(square.y1, square.y2);
        listCenters.push_back(center);
        
        // DEBUG
        //setPixel(center.first,center.second,255);
        std::cout << "Center: (" << center.first << "," << center.second << ")\n";
    }
    return listCenters;
}

void Planning::who_is_my_neighbour(std::vector<Room> hallways_center)
{
    std::vector<int> samlet;
    int j = 10000000;
    int iterator = 0;



    for (int i = 0; i < Lokale.size(); ++i) {
        std::cout << i << std::endl;
        samlet.push_back((abs(hallways_center[0].center.first - Lokale[i].center.first) + abs(hallways_center[0].center.second - Lokale[i].center.second)));
        samlet.push_back(abs(hallways_center[1].center.first -  Lokale[i].center.first) + abs(hallways_center[1].center.second - Lokale[i].center.second));
        samlet.push_back(abs(hallways_center[2].center.first -  Lokale[i].center.first) + abs(hallways_center[2].center.second - Lokale[i].center.second));
        samlet.push_back(abs(hallways_center[3].center.first -  Lokale[i].center.first) + abs(hallways_center[3].center.second - Lokale[i].center.second));
        samlet.push_back(abs(hallways_center[4].center.first -  Lokale[i].center.first) + abs(hallways_center[4].center.second - Lokale[i].center.second));
        samlet.push_back(abs(hallways_center[5].center.first -  Lokale[i].center.first) + abs(hallways_center[5].center.second - Lokale[i].center.second));
        if (Lokale[i].center.first > 4000) {

            std::cout <<i<< "if D" << abs(hallways_center[4].center.first -  Lokale[i].center.first) + abs(hallways_center[4].center.second - Lokale[i].center.second) << std::endl;
            std::cout << "if E" << abs(hallways_center[5].center.first -  Lokale[i].center.first) + abs(hallways_center[5].center.second - Lokale[i].center.second) << std::endl;

        }

        for (int k = 0; k <= 5; ++k) {
            if (samlet[k] < j) {
                iterator = k;
                j = samlet[k];
            }
        }

        switch (iterator) {
            case BLOK_A:
                std::cout << "lies in A" << std::endl;
                Lokale[i].distance = samlet[iterator];
                iterator = 0;
                j = 10000000;
                //img.setPixel(Lokale[i].center.first, Lokale[i].center.second, BLACK);
                blok_A.push(Lokale[i]);
                samlet.clear();
            break;
            case BIG_HALL:
                std::cout << "lies in Bighall" << std::endl;
                Lokale[i].distance = samlet[iterator];
                iterator = 0;
                j = 10000000;
                //img.setPixel(Lokale[i].center.first, Lokale[i].center.second, BLACK);
                Big_hall.push(Lokale[i]);
                samlet.clear();
            break;
            case BLOK_B:
                std::cout << "lies in B" << std::endl;
                Lokale[i].distance = samlet[iterator];
                iterator = 0;
                j = 10000000;
                //img.setPixel(Lokale[i].center.first, Lokale[i].center.second, BLACK);
                blok_B.push(Lokale[i]);
                samlet.clear();
            break;
            case BLOK_C:
                std::cout << "lies in C" << std::endl;
                Lokale[i].distance = samlet[iterator];
                iterator = 0;
                j = 10000000;
                //img.setPixel(Lokale[i].center.first, Lokale[i].center.second, BLACK);
                blok_C.push(Lokale[i]);
                samlet.clear();
            break;
            case BLOK_D:
                std::cout << "lies in D" << std::endl;
                Lokale[i].distance = samlet[iterator];
                iterator = 0;
                j = 10000000;
                //img.setPixel(Lokale[i].center.first, Lokale[i].center.second, BLACK);
                blok_D.push(Lokale[i]);
                samlet.clear();
            break;
            case BLOK_E:
                std::cout << "lies in E" << std::endl;
                Lokale[i].distance = samlet[iterator];
                iterator = 0;
                j = 10000000;
                //img.setPixel(Lokale[i].center.first, Lokale[i].center.second, BLACK);
                blok_E.push(Lokale[i]);
                samlet.clear();
            break;


        };

    };

};
