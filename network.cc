#include "network.h"

#include <utility>
#include <sstream>
#include <regex>
#include <limits>
#include <queue>
#include <iostream>
#include <fstream>
#include <cmath>

Network::Network(const std::string& airports_filename, const std::string& flights_filename) {
  parseAirports(airports_filename);
  parseFlights(flights_filename);
}

const FlightGraph& Network::GetGraph() const {
  return graph_;
}

void Network::parseAirports(const std::string& filename) {
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
      graph_[a.getCode()] = std::unordered_map<std::string, double>();
      airports_[a.getCode()] = a;
    }
  }
}

void Network::parseFlights(const std::string& filename) {
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
      if (airports_.count(components[2]) == 1 && airports_.count(components[4]) == 1) {
        graph_[components[2]][components[4]] = ComputeDistance(components[2], components[4]);
      }
    }
  }
}

double Network::ComputeDistance(const std::string& a1, const std::string& a2) const {
  double to_radians = 3.14159265358979323846 / 180.0;
  double lat1 = airports_.at(a1).getLatitude();
  double long1 = airports_.at(a1).getLongitude();
  double lat2 = airports_.at(a2).getLatitude();
  double long2 = airports_.at(a2).getLongitude();
  double haversine = 0.5 - cos((lat2 - lat1) * to_radians) / 2
      + cos(lat1 * to_radians) * cos(lat2 * to_radians) *
          (1 - cos((long2 - long1) * to_radians)) / 2;
  return 2 * R * asin(sqrt(haversine));
}

double Network::ComputeShortestPath(const std::string& a1, const std::string& a2) const {
  //@TODO Implement this function

  std::priority_queue<std::pair<double, std::string>> queue;
  std::unordered_map<std::string, double> distances;

  for (const auto& it : airports_) distances[it.first] = std::numeric_limits<double>::max();

  queue.emplace(0, a1);

  while (!queue.empty()) {
    std::pair<double, std::string> element = queue.top(); queue.pop();
    double current_distance = element.first;
    std::string current_airport = element.second;

    if (current_distance < distances[current_airport]) {
      distances[current_airport] = current_distance;
      for (auto& it : graph_.at(current_airport)) {
        if (current_distance + it.second < distances[it.first]) queue.emplace(current_distance + it.second, it.first);
      }
    }
  }

  return distances[a2];
}

