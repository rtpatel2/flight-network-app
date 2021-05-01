#include <string>
#include <vector>	
#include "../catch/catch.hpp"
#include "../airport.h"

#include "../network.h"

Network full_net("tests/data/airports.txt", "tests/data/routes.txt");
Network small_net("tests/data/airports_small.txt", "tests/data/routes_small.txt");

static constexpr double kEpsilon = 0.01;

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
      if (it->first.getCode() == "GKA") {
        REQUIRE(it->second.begin()->first.getCode() == "MAG");
      }
      if (it->first.getCode() == "UAK") {
        REQUIRE(it->second.begin()->first.getCode() == "SFJ");
      }
    }
  }
}

TEST_CASE("Validate distance computation") {
  FlightGraph graph = full_net.GetGraph();

  SECTION("One way flight") {
    Airport kzn("KZN", 55.606201171875, 49.278701782227);
    Airport aer("AER", 43.449902, 39.9566);
    REQUIRE(graph[kzn][aer] == Approx(936.25).epsilon(kEpsilon));
  }

  SECTION("Two way flight") {
    Airport lax("LAX", 33.94250107, -118.4079971);
    Airport syd("SYD", -33.94609832763672, 151.177001953125);
    REQUIRE(graph[lax][syd] == Approx(7488).epsilon(kEpsilon));
    REQUIRE(graph[syd][lax] == Approx(7488).epsilon(kEpsilon));
  }

  SECTION("Compute shortest path between two airports") {
    Airport lax("LAX", 33.94250107, -118.4079971);
    Airport syd("SYD", -33.94609832763672, 151.177001953125);
    REQUIRE(small_net.ComputeShortestPath(lax, syd) == Approx(7488).epsilon(kEpsilon));
  }
}