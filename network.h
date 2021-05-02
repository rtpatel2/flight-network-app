#pragma once

#include "airport.h"
#include <string>
#include <unordered_map>

typedef std::unordered_map<std::string, std::unordered_map<std::string, double>> FlightGraph;

/** Network class maintains airports and flights between them. */
class Network {
 public:
  /**
   * Constructor takes a CSV filename for airports and flights to parse.
   * @param airports_filename the CSV file containing entries for airports
   * @param flights_filename the CSV file containing entries for flights
   */
  Network(const std::string& airports_filename, const std::string& flights_filename);

  /**
   * Computes the distance of the shortest path from one airport to all other airports, going through recorded flights.
   * @param a1 starting airport code
   * @return map of airport to distance of shortest paths, in miles
   */
  std::unordered_map<std::string, double> ComputeShortestPath(const std::string& a1) const;

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
   * @param a1 first airport code
   * @param a2 second airport code
   * @return distance between the two airports, in miles
   */
  double ComputeDistance(const std::string& a1, const std::string& a2) const;

private:
  FlightGraph graph_;
  std::unordered_map<std::string, Airport> airports_;
};