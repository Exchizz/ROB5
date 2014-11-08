#include <iostream>
#include <vector>
#include "Image.h"
int main(){
	Image myImage;
	//myImage.loadImage("image.pgm");
	myImage.createImage("my_image.pgm", 100, 100); // as a  fourth parameter, max value can be given - default is 255(8 bit greyscale)

	for(int x = 0; x < myImage.getWidth() +1; ++x){
		for(int y = 0; y < myImage.getHeight() ; ++y ){
			std::cout << "x,y: " << x << " " << y << " \t";
			std::cout << "value: " << x+y << std::endl;
			 myImage.setPixel(x,y, x+y);
		}

	}
	std::cout << "Hello World\n";
	return 0;
}
