#pragma once
#include "cs225/PNG.h"
#include "network.h"
#include "cs225/Animation.h"
#include <string>
typedef const std::unordered_map<std::string, Airport> AirportList;

class Map {
    public:
        Map(cs225::PNG& map);
        void AddPoint(double lat, double lng);
        cs225::PNG& GetMap();
        void Animate(const FlightGraph& graph, AirportList& airports, const std::string& origin, std::string& filename);

    private:
        cs225::PNG map;
};