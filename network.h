#pragma once

#include <string>
#include <unordered_map>

#include "airport.h"
#include "kdtree.h"

typedef std::unordered_map<std::string, std::unordered_map<std::string, double>>
    FlightGraph;

/** Network class maintains airports and flights between them. */
class Network {
 public:
  /**
   * Constructor takes a CSV filename for airports and flights to parse.
   * @param airports_filename the CSV file containing entries for airports
   * @param flights_filename the CSV file containing entries for flights
   */
  Network(const std::string& airports_filename,
          const std::string& flights_filename);

  /**
   * Computes the distance of the shortest path from one airport to all other
   * airports, going through recorded flights.
   * @param a1 starting airport code
   * @return map of airport to distance of shortest paths, in miles
   */
  std::unordered_map<std::string, double> ComputeShortestPaths(
      const std::string& a1) const;

  /**
   * Finds the best airport for two friends to meet, given their two starting
   * airports.
   * @param a1 first airport code
   * @param a2 second airport code
   * @param tolerance a tolerance between 0 and 0.5 to weight fairness of travel distances.
   * Tolerance dictates the minimum portion of the distance traveled by each friend out of
   * the total distance traveled by both friends together.
   * A tolerance of 0 will allow both friends to meet at one of the friends' origin airports, whereas
   * a tolerance of 0.5 will require the travel distances be equal.
   * @return airport code of the optimal airport for the friends to meet
   */
  std::string FindBestAirport(const std::string& a1, const std::string& a2,
                              double tolerance) const;

  /**
   * Finds the closest airport to the specified latitude and longitude values
   * using a KDTree.
   * @param lat latitude
   * @param lng longitude
   * @return airport code of the nearest airport
   */
  std::string FindClosestAirport(double lat, double lng);

  const FlightGraph& GetGraph() const;

  const std::unordered_map<std::string, Airport>& GetAirports() const;

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
   * Computes the great-circle distance between two airports joined with a
   * direct flight.
   * @param a1 first airport code
   * @param a2 second airport code
   * @return distance between the two airports, in miles
   */
  double ComputeDistance(const std::string& a1, const std::string& a2) const;

 private:
  FlightGraph graph_;
  std::unordered_map<std::string, Airport> airports_;
  KDTree kd_;
};