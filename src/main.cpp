#include <iostream>
#include <vector>
#include "Image.h"
int main(){
	Image myImage;
	myImage.loadImage("image.pgm");

	myImage.setPixel(10,5,100);
	myImage.saveImage("myimage_output.pgm");
	std::cout << "Hello World\n";
	return 0;
}
