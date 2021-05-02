#include <iostream>
#include <vector>
#include "cs225/HSLAPixel.h"
#include "cs225/PNG.h"
#include "cs225/Animation.h"
#include "map.cc"
#include "airport.cc"
int main() {
	std::cout<<"main has compiled"<<std::endl;
	Animation a;
	cs225::HSLAPixel b;
	 cs225::PNG png;       png.readFromFile("white.png");
	 	 cs225::PNG png2;       png2.readFromFile("myFloodFill.png");

	 	std::cout<<"png read"<<std::endl;

	a.addFrame(png);
		a.addFrame(png2);

	a.write("myFloodFill.gif");

	
  	cs225::PNG lastFrame = a.getFrame( 0 );
 	//lastFrame.writeToFile("myFloodFill.png");

	//Map m(png);
	Airport asdfg;
	return 0;
}
