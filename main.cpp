#include "cs225/HSLAPixel.h"
#include "cs225/PNG.h"
#include "cs225/Animation.h"
#include "map.cc"
#include "airport.cc"
#include "network.cc"
#include "kdtree.cc"

#include <iostream>
#include <vector>
#include <string>

int main(int argc, char *argv[]) {
	std::vector<std::string> inputs;
	for (int i = 0; i < argc; ++i) {
		inputs.push_back(argv[i]);
	}
	
	if (inputs[1] == "find_best_airport") {
		// ./flights find_best_airport <airport_data> <flight_data> <first_airport> <second_airport> [tolerance]
		if (argc < 6) {
			std::cout << "Not enough arguments" << std::endl;
		} else {
			Network network(inputs[2], inputs[3]);

			if (network.GetAirports().count(inputs[4]) == 0 || network.GetAirports().count(inputs[5]) == 0) {
				std::cout << "Invalid airport(s)" << std::endl;
			} else {
				double tol = 0.25;
				if (argc >= 7) {
					tol = std::stod(inputs[6]);
				} else {
					std::cout << "No tolerance provided, using 0.25 as a default" << std::endl;
				}
				std::cout << "Finding best airport to meet..." << std::endl;
				std::cout << network.FindBestAirport(inputs[4], inputs[5], tol) << std::endl;
			}
		}
	} else if (inputs[1] == "animate_bfs") {
		// ./flights animate_bfs <airport_data> <flight_data> <starting_airport> <gif_output_file> <last_frame_output_file>
		if (argc < 7) {
			std::cout << "Not enough arguments" << std::endl;
		} else {
			Network network(inputs[2], inputs[3]);
			
			if (network.GetAirports().count(inputs[4]) == 0) {
				std::cout << "Invalid airport" << std::endl;
			} else {
				std::cout << "Animating BFS from " << inputs[4] << "..." << std::endl;
				cs225::PNG png;
				png.readFromFile("mercator.png");
				Map map(png);
				map.Animate(network.GetGraph(), network.GetAirports(), inputs[4], inputs[5], inputs[6]);
				std::cout << "Animation successful!" << std::endl;
			}
		}
	} else if (inputs[1] == "find_closest_airport") {
		// ./flights find_closest_airport <airport_data> <flight_data> <starting_latitude> <starting_longitude>
		if (argc < 6) {
			std::cout << "Not enough arguments" << std::endl;
		} else {
			Network network(inputs[2], inputs[3]);
			std::cout << "Finding closest airport..." << std::endl;
			std::cout << network.FindClosestAirport(std::stod(inputs[4]), std::stod(inputs[5])) << std::endl;
		}
	}

	return 0;
}