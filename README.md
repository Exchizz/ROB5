ROB5
====


V2.

    Updating image-class.
     - Now save using saveImage(filename)
     - Open using loadImage();
    
    Mutators/Accessors:
     - getPixel(x,y);
     - setPixel(x,y, val);


How to use image class:
class name: Image
  @No parms in constructor

Create image:
  obj.createImage(filename, width, height, maxvalue = 255);

Open image:
 obj.loadImage(filename);


Get pixel:
  int obj.getPixel(width, height);


Set pixel:
   void obj.setPixel(width, height, value);


Get image properties:
   int obj.getWidth();
   int obj.getHeight();
   int obj.getMaxValue();
   string obj.getVersion();
