#include <catch2/catch.hpp>

#include "core/network.h"

Network net("airports.txt", "routes.txt");
static constexpr double kEpsilon = 0.01;

TEST_CASE("file reading") {
    //@TODO Implement SECTIONs to validate parsing
}

TEST_CASE("Validate distance computation") {
    FlightGraph graph = net.GetGraph();

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
}