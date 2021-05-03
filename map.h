#pragma once
#include "cs225/PNG.h"
#include "network.h"

class Map {
    public:
        Map(cs225::PNG& map);
        void AddPoint(double lat, double lng);
        cs225::PNG& GetMap();

    private:
        cs225::PNG map;
};