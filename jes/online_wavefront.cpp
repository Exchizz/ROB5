//============================================================================
// Name        : Wavefront_online.cpp
// Author      : jejep12
// Version     : v2
// Description : Wavefront: online version
//============================================================================

#include "onlineWaveFront.h"

struct vector2D {
public:
    vector2D() :x(-1), y(-1) {}
    vector2D(double x, double y) : x(x), y(y){}

    friend const vector2D operator-(const vector2D& a, const vector2D& b) { return vector2D(a.x - b.x, a.y - b.y); }
    friend double dist2(const vector2D& a, const vector2D& b){ return (b - a).norm2(); }

    int getX(){ return x; }
    int getY(){ return y; }
    void setXY(int x, int y){
        setX(x);
        setY(y);
    }
    void setX(int x){ this->x = x; }
    void setY(int y){ this->y = y; }
private:
    double x, y;
    double norm2() const { return sqrt(x*x + y*y); }
};

// Struct to keep track of coordinates
struct coordinate
{
public:
    int wgetX(){return x;}
    int wgetY(){return y;}
    void wsetX(int x){ this->x = x; }
    void wsetY(int y){ this->y = y; }
private:
    int x;
    int y;

};

onlineWaveFront::onlineWaveFront(Image &tempImg){
    // Load map
    std::cout << "Loading Map" << std::endl;

//    img.loadImage(filename.c_str());
    img = tmpImg;
    xHeight = img.getHeight();
    xWidth = img.getWidth();

    std::cout << "Constructed" << std::endl;
};

void onlineWaveFront::makeWaveFront(int robotPOSX,int robotPOSY, int goalPOSX,int goalPOSY){
    int tempX, tempY;

    // Set robot initial location and goal
    vector2D robot(robotPOSX, robotPOSY);
    vector2D goal(goalPOSX, goalPOSY);

    // Make a matrix to hold map
    int** map_matrix = new int*[xHeight];
    for (int i = 0; i < xHeight; i++)
        map_matrix[i] = new int[xWidth];

    //Transform the map to One's and Zero's
    for (int y = 0; y < img.getHeight(); y++){
        for (int x = 0; x < img.getWidth(); x++){
            if (img.getPixel(x, y) == 255)
                map_matrix[y][x] = 0;
            else
                map_matrix[y][x] = 1;
        }
    }

    std::cout << "Initial State Finished" << std::endl;

    // Label the goal with a two
    map_matrix[goal.getY()][goal.getX()] = 2;

    //Create buffers that will hold locations of last visited values
    coordinate* wavebuffer = new coordinate[xHeight*xWidth];
    coordinate* wavebuffer2 = new coordinate[xHeight*xWidth];

    //Put goal into wavefrontbuffer
    wavebuffer2[0].wsetX(goal.getX());
    wavebuffer2[0].wsetY(goal.getY());

    //Make the wave
    //Run until robot's location has a value
    while (map_matrix[robot.getY()][robot.getX()] == 0)
    {
        listsize = listsize2-1;
        listsize2=0;
        incValue++;

        //Copy buffer 2 to buffer 1
        for(int i=0; i<=listsize; i++){wavebuffer[i] = wavebuffer2[i];}

        //Go through all coordinates set in preveous iteration
        for(int j=0; j <= listsize ; j++)
        {
            //Location to inspect is loaded
            int x = wavebuffer[j].wgetX();
            int y = wavebuffer[j].wgetY();

            //Do for each connection (four in this case)
            for ( int i = 0; i < 4; i++ )
            {
                switch (i)
                {
                case 0:
                    tempY = y - 1;
                    tempX = x;
                    break;
                case 1:
                    tempY = y + 1;
                    tempX = x;
                    break;
                case 2:
                    tempY = y;
                    tempX = x - 1;
                    break;
                case 3:
                    tempY = y;
                    tempX = x + 1;
                    break;
                }

                //If connected pixel is not a wall or obstacle set value to incValue(the incrementing value)
                if (tempX <= xWidth - 1 && tempY <= xHeight - 1 && tempX > 0 && tempY > 0)
                {
                    //only if there is no value there
                    if (map_matrix[tempY][tempX] == 0)
                    {
                        map_matrix[tempY][tempX] = incValue;
                        wavebuffer2[listsize2].wsetX(tempX);
                        wavebuffer2[listsize2].wsetY(tempY);
                        listsize2++;
                    }
                }
            }
        }
    }
    // Plan/Run route
    while (true){
        //Get value at robots location
        incValue = map_matrix[robot.getY()][robot.getX()];

        // For all connecting points try to find a value that is less than the current
        // Directions up and right are preferred
        // When found change pixelvalue and increment moves
        for (int i = 0; i < 4; i++){
            switch (i){
            case 3:
                tempY = robot.getY() - 1;
                tempX = robot.getX();
                break;
            case 1:
                tempY = robot.getY() + 1;
                tempX = robot.getX();
                break;
            case 2:
                tempY = robot.getY();
                tempX = robot.getX() - 1;
                break;
            case 0:
                tempY = robot.getY();
                tempX = robot.getX() + 1;
                break;
            }

            if (tempX <= xWidth - 1 && tempY <= xHeight - 1 && tempX > 0 && tempY > 0){
                if (incValue > map_matrix[tempY][tempX] && map_matrix[tempY][tempX] != 1){
                    robot.setXY(tempX, tempY);
                    img.setPixel(tempX, tempY, 80);
                    break;
                }
            }
        }
        //If goal is reached break loop
        if (robot.getY() == goal.getY() && robot.getX() == goal.getX())
            break;
    }
    std::cout << "WaveFront Done" << std::endl;
    // save image
    std::cout << "Saving image" << std::endl;
    img.saveImage("tmp2");

    // cleanup
    std::cout << "Cleaned up and Done" << std::endl;
    delete wavebuffer;
    delete wavebuffer2;
}

