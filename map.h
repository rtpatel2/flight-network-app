#pragma once

#include <string>

#include "cs225/Animation.h"
#include "cs225/PNG.h"
#include "network.h"

typedef std::unordered_map<std::string, Airport> AirportMap;
typedef std::unordered_map<std::string, std::unordered_map<std::string, double>>
    FlightGraph;

/** Maintains functionality of a Mercator projection of a globe. */
class Map {
 public:
  /**
   * Creates a map with the given PNG background.
   * @param map PNG background
   */
  Map(const cs225::PNG& map);

  /**
   * Adds a point to this map.
   * @param lat latitude to add to the map
   * @param lng longitude to add to the map
   * @param luminance luminance of pixels modified by adding a point
   */
  void AddPoint(double lat, double lng, double luminance);

  /**
   * Creates an animation of a BFS.
   * @param graph an undirected graph of flights between airports
   * @param airports a map between 3-letter airport codes and airport objects
   * @param origin 3-letter airport code of the starting point of the BFS
   * @param gif_filename filename to which to save GIF animation of BFS
   * @param png_filename filename to which to save last frame of BFS animation
   */
  void Animate(const FlightGraph& graph, const AirportMap& airports,
               const std::string& origin, const std::string& gif_filename,
               const std::string& png_filename);

  /**
   * Projects a given latitude and longitude to coordinates on a mercator
   * projection.
   * @param lat latitude
   * @param lng longitude
   * @return a pair of (x, y) representing the coordinates on the projection
   */
  std::pair<double, double> ProjectMercator(double lat, double lng);

  cs225::PNG& GetMap();

 private:
  cs225::PNG map_;
};