#include "cs225/HSLAPixel.h"
#include "cs225/PNG.h"
#include "cs225/Animation.h"
#include "map.cc"
#include "airport.cc"
#include "network.cc"

#include <iostream>
#include <vector>
#include <string>

static Network network("tests/data/airports.txt", "tests/data/routes.txt");

int main(int argc, char *argv[]) {
	std::vector<std::string> inputs;
	for (int i = 0; i < argc; ++i) {
		inputs.push_back(argv[i]);
	}

	
	if (inputs[1] == "find_best_airport") {
		// ./flights find_best_airport <first_airport> <second_airport> <tolerance>
		if (argc < 5) {
			std::cout << "Not enough arguments" << std::endl;
		} else if (network.GetAirports().count(inputs[2]) == 0 || network.GetAirports().count(inputs[3]) == 0) {
			std::cout << "Invalid airports" << std::endl;
		} else {
			std::cout << "Finding best airport to meet..." << std::endl;
			std::cout << network.FindBestAirport(inputs[2], inputs[3], std::stod(inputs[4])) << std::endl;
		}
	}
	// std::cout<<"main has compiled"<<std::endl;

	// Network full_net("tests/data/airports.txt", "tests/data/routes.txt");
	// cs225::PNG png;
	// png.readFromFile("mercator.png");
	// Map m2(png);
	// std::string file = "bfs.gif";
	// // m2.Animate(full_net.GetGraph(), full_net.GetAirports(), "ZMH", file);	
	// m2.Animate(full_net.GetGraph(), full_net.GetAirports(), "ORD", file, "last_frame_bfs.png");		

	return 0;
}

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