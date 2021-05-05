#include <string>
#include <vector>	
#include <unordered_map>
#include <utility>
#include "../catch/catch.hpp"
#include "../airport.h"

#include "../network.h"
#include "../map.h"
#include "../kdtree.h"

Network full_net("tests/data/airports.txt", "tests/data/routes.txt");
Network small_net("tests/data/airports_small.txt", "tests/data/routes_small.txt");

static constexpr double kEpsilon = 0.01;

TEST_CASE("Draw airports") {
  cs225::PNG png;       png.readFromFile("mercator.png");
  Map m(png);
    std::unordered_map<std::string, Airport> airports = full_net.GetAirports();
    for(auto& it: airports) {
      m.AddPoint(it.second.getLatitude(), it.second.getLongitude());
    }
    REQUIRE(!airports.empty());
  m.GetMap().writeToFile("airport_map.png");
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

TEST_CASE("test_ComputeDistance") {
  FlightGraph graph = full_net.GetGraph();

  SECTION("One way flight") {
    REQUIRE(graph["KZN"]["AER"] == Approx(936.25).epsilon(kEpsilon));
  }

  SECTION("Two way flight") {
    REQUIRE(graph["LAX"]["SYD"] == Approx(7488).epsilon(kEpsilon));
    REQUIRE(graph["SYD"]["LAX"] == Approx(7488).epsilon(kEpsilon));
  }
}

TEST_CASE("test_ComputeShortestPaths") {
  SECTION("Shortest path with direct flight") {
    REQUIRE(full_net.ComputeShortestPaths("LAX")["SYD"] == Approx(7488).epsilon(kEpsilon));
  }
  
  SECTION("Shortest path with one layover") {
    REQUIRE(full_net.ComputeShortestPaths("LGA")["SFO"] == Approx(2573).epsilon(kEpsilon));
  }
}

TEST_CASE("test_FindBestAirport") {
  SECTION("Best airport within the US") {
    REQUIRE(full_net.FindBestAirport("LAX", "JFK", 0.35) == "MCI");
  }

  SECTION("Best airport across Europe") {
    REQUIRE(full_net.FindBestAirport("CDG", "VVO", 0.45) == "TJM");
  }

  SECTION("Best airport across the world") {
    REQUIRE(full_net.FindBestAirport("NRT", "LAX", 0.25) == "HNL");
  }

  SECTION("Tolerance too high") {
    REQUIRE(full_net.FindBestAirport("JFK", "DFW", 0.5) == "No possible airport! Try a boat instead...");
  }

  SECTION("No possible way to connect via flights") {
    REQUIRE(small_net.FindBestAirport("GKA", "UAK", 0) == "No possible airport! Try a boat instead...");
  }
}

TEST_CASE("test_FindNearestNeighbors") {
  std::vector<Airport> airports;
  for (auto& it : full_net.GetAirports()) {
    airports.push_back(it.second);
  }
  KDTree kd(airports);

  SECTION("Basic tests") {
    Airport a2("a2", 37.289498, -121.796731);
    REQUIRE(kd.findNearestNeighbor(a2).getCode() == "RHV");

    Airport a3("a3", 1.359758, 103.883477);
    REQUIRE(kd.findNearestNeighbor(a3).getCode() == "QPG");

    Airport a4("a4", 42.143537, -87.867137);
    REQUIRE(kd.findNearestNeighbor(a4).getCode() == "PWK");
  }

  SECTION("Fence jumping") {
    Airport a1("a1", 40.560806, -74.465591);
    REQUIRE(kd.findNearestNeighbor(a1).getCode() == "LDJ");
  }
}
