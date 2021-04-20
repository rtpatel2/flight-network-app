#include <catch2/catch.hpp>

#include "core/network.h"

TEST_CASE("file reading") {
    Network net("airports.txt", "./tests/data/routes.txt");
}
