#pragma once

#include <string>
#include <unordered_map>
#include "core/airport.h"

typedef std::unordered_map<Airport, std::unordered_map<Airport, double>> FlightGraph;

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
    Network(const std::string& airports_filename, const std::string& flights_filename);

    const FlightGraph& GetGraph() const;

    /** Radius of the earth, in miles. */
    static constexpr double R = 3963.1676;

  private:
    /**
     * Populates graph with airports.
     * @param filename the CSV file with airports.
     */
    void parseAirports(const std::string& filename);

    /**
     * Populates graph with flights. Method assumes that airports already exist.
     * @param filename the CSV file containing entries for flights
     */
    void parseFlights(const std::string& filename);

    /**
     * Computes the great-circle distance between two airports joined with a direct flight.
     * @param a1 first airport
     * @param a2 second airport
     * @return distance between the two airports, in miles
     */
    double ComputeDistance(const Airport& a1, const Airport& a2) const;

    /**
     * Computes the distance of the shortest path between two airports, going through recorded flights.
     * @param a1 first airport
     * @param a2 second airport
     * @return distance of the shortest path, in miles
     */
    double ComputeShortestPath(const airport& a1, const Airport& a2) const;

    FlightGraph graph_;
    std::unordered_map<std::string, Airport> airports_;
};