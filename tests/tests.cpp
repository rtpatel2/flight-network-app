#include <string>
#include <vector>	
#include <unordered_map>
#include <utility>
#include "../catch/catch.hpp"
#include "../airport.h"
#include "../cs225/PNG.h"
#include "../network.h"
#include "../map.h"
#include "../kdtree.h"

Network full_net("tests/data/airports.txt", "tests/data/routes.txt");
Network small_net("tests/data/airports_small.txt", "tests/data/routes_small.txt");

static constexpr double kEpsilon = 0.01;

TEST_CASE("Draw airports") {
  cs225::PNG png;       
  png.readFromFile("mercator.png");
  Map m(png);
  std::unordered_map<std::string, Airport> airports = full_net.GetAirports();

  for(auto& it: airports) {
    m.AddPoint(it.second.getLatitude(), it.second.getLongitude(), 0.5);
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
    REQUIRE(kd.findNearestNeighbor(37.289498, -121.796731).getCode() == "RHV");
    REQUIRE(kd.findNearestNeighbor(1.359758, 103.883477).getCode() == "QPG");
    REQUIRE(kd.findNearestNeighbor(42.143537, -87.867137).getCode() == "PWK");
  }

  SECTION("Fence jumping") {
    REQUIRE(kd.findNearestNeighbor(40.560806, -74.465591).getCode() == "LDJ");
  }
}

TEST_CASE("test_ProjectMercator") {
  cs225::PNG png; png.readFromFile("tests/data/mercator.png");
  Map map(png);

  std::pair<double, double> projection = map.ProjectMercator(-6.081689834590001, 145.391998291);
  REQUIRE(projection.first == Approx(1084.64).epsilon(kEpsilon));
  REQUIRE(projection.second == Approx(620.31).epsilon(kEpsilon));

  projection = map.ProjectMercator(65.2833023071289, -14.401399612426758);
  REQUIRE(projection.first == Approx(552).epsilon(kEpsilon));
  REQUIRE(projection.second == Approx(310.04).epsilon(kEpsilon));
}

TEST_CASE("test_AddPoint") {
  cs225::PNG png; png.readFromFile("tests/data/mercator.png");
  Map map(png);

  map.AddPoint(-6.081689834590001, 145.391998291, 0.5);

  REQUIRE(map.GetMap().getPixel(1083, 619).h == 265);
  REQUIRE(map.GetMap().getPixel(1083, 619).s == 1);
  REQUIRE(map.GetMap().getPixel(1083, 619).l == 0.5);
  REQUIRE(map.GetMap().getPixel(1083, 619).a == 1);

  map.AddPoint(65.2833023071289, -14.401399612426758, 0.23);

  REQUIRE(map.GetMap().getPixel(551, 309).h == 265);
  REQUIRE(map.GetMap().getPixel(551, 309).s == 1);
  REQUIRE(map.GetMap().getPixel(551, 309).l == 0.23);
  REQUIRE(map.GetMap().getPixel(551, 309).a == 1);
}