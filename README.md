ROB5
====
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
