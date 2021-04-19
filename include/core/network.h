#pragma once

#include <string>
#include <unordered_map>

/**
 * Network class maintains airports and flights between them.
 */
class Network {
public:
    /**
     * Constructor takes a CSV filename for airports and flights to parse.
     * @param airports_filename the CSV file containing entries for airports
     * @param flights_filename the CSV file containing entries for flights
     */
    Network(std::string airports_filename, std::string flights_filename);

private:
    /**
     * Populates graph with airports.
     * @param filename the CSV file with airports.
     */
    void parseAirports(std::string filename);

    /**
     * Populates graph with flights. Method assumes that airports already exist.
     * @param filename the CSV file containing entries for flights
     */
    void parseFlights(std::string filename);
    std::unordered_map<std::string, std::unordered_map<std::string, double>> graph_;
};