#include "core/network.h"

#include <utility>
#include <fstream>
#include <iostream>

Network::Network(std::string airports_filename, std::string flights_filename) {
    parseAirports(std::move(airports_filename));
    parseFlights(std::move(flights_filename));
}

void Network::parseAirports(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;
    while (std::getline(file, line)) {
        std::cout<<line<<std::endl;
    }
}

void Network::parseFlights(const std::string& filename) {

}
