#include <iostream>
#include <vector>
#include "cs225/HSLAPixel.h"
#include "cs225/PNG.h"
#include "cs225/Animation.h"
#include "map.cc"
#include "airport.cc"
#include "network.cc"
#include <string>
int main() {
	std::cout<<"main has compiled"<<std::endl;
	// cs225::HSLAPixel b;
	//  cs225::PNG png;       png.readFromFile("white.png");
	//  	 cs225::PNG png2;       png2.readFromFile("myFloodFill.png");

	//  	std::cout<<"png read"<<std::endl;

	// a.addFrame(png);
	// 	a.addFrame(png2);

	// a.write("BFS.gif");

	
  	// cs225::PNG lastFrame = a.getFrame( 0 );
 	// //lastFrame.writeToFile("myFloodFill.png");

	// //Map m(png);
	// Airport asdfg;
	Network full_net("tests/data/airports.txt", "tests/data/routes.txt");
	cs225::PNG png;
	png.readFromFile("mercator.png");
	Map m2(png);
	std::string file = "bfs.gif";
  	m2.Animate(full_net.GetGraph(), full_net.GetAirports(), "ORD", file);		
	return 0;
}
