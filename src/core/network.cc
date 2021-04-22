#include "core/network.h"
#include "cinder/gl/gl.h"

#include <utility>
#include <sstream>
#include <regex>
#include <cmath>

Network::Network(const std::string& airports_filename, const std::string& flights_filename) {
    parseAirports(airports_filename);
    parseFlights(flights_filename);
}

void Network::parseAirports(const std::string &filename) {
    std::ifstream file(filename);
    std::string line;
    while (std::getline(file, line)) {
        std::vector<std::string> components;
        std::string component;
        std::stringstream current_line(line);
        while (getline(current_line, component, ',')) {
            components.push_back(component);
        }
        if (components.size() == 14) {
            components[4].erase(remove(components[4].begin(), components[4].end(), '\"'), components[4].end());
            Airport a(components[4], std::stod(components[6]), std::stod(components[7]));
            graph_[a] = std::unordered_map<Airport, double>();
            airports_[a.getCode()] = a;
        }
    }
}

void Network::parseFlights(const std::string &filename) {
    std::ifstream file(filename);
    std::string line;
    while (std::getline(file, line)) {
        std::vector<std::string> components;
        std::string component;
        std::stringstream current_line(line);
        while (getline(current_line, component, ',')) {
            components.push_back(component);
        }
        if (components.size() >= 5) {
            components[2].erase(remove(components[2].begin(), components[2].end(), '\"'), components[2].end());
            components[4].erase(remove(components[4].begin(), components[4].end(), '\"'), components[4].end());
            Airport a(components[2], 0, 0);
            Airport b(components[4], 0, 0);
            graph_[a][b] = ComputeDistance(airports_[a.getCode()], airports_[b.getCode()]);
        }
    }
}

double Network::ComputeDistance(const Airport& a1, const Airport& a2) const {
    double to_radians = M_PI / 180.0;
    double lat1 = a1.getLatitude();
    double long1 = a1.getLongitude();
    double lat2 = a2.getLatitude();
    double long2 = a2.getLongitude();
    double haversine = 0.5 - cos((lat2 - lat1) * to_radians) / 2
                       + cos(lat1 * to_radians) * cos(lat2 * to_radians) *
                         (1 - cos((long2 - long1) * to_radians)) / 2;
    return 2 * R * asin(sqrt(haversine));
}
