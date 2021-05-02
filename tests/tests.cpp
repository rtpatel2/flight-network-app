#include <string>
#include <vector>	
#include <unordered_map>
#include "../catch/catch.hpp"
#include "../airport.h"

#include "../network.h"
#include "../map.h"

Network full_net("tests/data/airports.txt", "tests/data/routes.txt");
Network small_net("tests/data/airports_small.txt", "tests/data/routes_small.txt");

static constexpr double kEpsilon = 0.01;
TEST_CASE("Draw airports") {
  cs225::PNG png;       png.readFromFile("mercator.png");
  Map m(png);
    std::unordered_map<std::string, Airport> airports = full_net.GetAirports();
    for(auto& it: airports) {
      m.addPoint(it.second.getLatitude(), it.second.getLongitude());
    }
    REQUIRE(!airports.empty());

  m.getMap().writeToFile("airport_map.png");
}
TEST_CASE("file reading") {
  //@TODO Implement SECTIONs to validate parsing
  FlightGraph graph = small_net.GetGraph();

  SECTION("Confirm number of existing flight routes") {
    size_t count_flights = 0;
    for (auto it = graph.begin(); it != graph.end(); ++it) {
      if (!it->second.empty()) {
        ++count_flights;
      }
    }
    REQUIRE(count_flights == 3);
  }

  SECTION("Confirm two flight routes exist from dataset") {
    for (auto it = graph.begin(); it != graph.end(); ++it) {
      if (it->first == "GKA") {
        REQUIRE(it->second.begin()->first == "MAG");
      }
      if (it->first == "UAK") {
        REQUIRE(it->second.begin()->first == "SFJ");
      }
    }
  }
}

TEST_CASE("Validate distance computation") {
  FlightGraph graph = full_net.GetGraph();

  SECTION("One way flight") {
    REQUIRE(graph["KZN"]["AER"] == Approx(936.25).epsilon(kEpsilon));
  }

  SECTION("Two way flight") {
    REQUIRE(graph["LAX"]["SYD"] == Approx(7488).epsilon(kEpsilon));
    REQUIRE(graph["SYD"]["LAX"] == Approx(7488).epsilon(kEpsilon));
  }

  SECTION("Compute shortest path between two airports") {
    REQUIRE(small_net.ComputeShortestPath("LAX")["SYD"] == Approx(7488).epsilon(kEpsilon));
  }
}