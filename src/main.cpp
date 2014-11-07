#include <iostream>
#include <vector>
#include "Image.h"
int main(){
	Image myImage;
	//myImage.loadImage("image.pgm");
	myImage.createImage("my_image.pgm", 100, 100);

	for(int x = 0; x < myImage.getWidth(); ++x){
		for(int y = 0; y < myImage.getHeight(); ++y ){
			std::cout << "x,y: " << x << " " << y << " \t";
			//std::cout << "value: " << myImage.setPixel(x,y, x+y) << std::endl;
			std::cout << "value: " << x+y << std::endl;
			 myImage.setPixel(x,y, x+y);
		}

	}
	std::cout << "Hello World\n";
	return 0;
}
