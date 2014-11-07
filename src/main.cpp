#include <iostream>
#include <vector>
#include "Image.h"
int main(){
	Image myImage;
	myImage.loadImage("image.pgm");

	for(int x = 0; x < myImage.getWidth(); ++x){
		for(int y = 0; y < myImage.getHeight(); ++y ){
			std::cout << "x,y: " << x << " " << y << " \t";
			std::cout << "value: " << myImage.getPixel(x,y) << std::endl;
		}

	}
	std::cout << "Hello World\n";
	return 0;
}
