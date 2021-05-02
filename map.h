#pragma once
#include "cs225/PNG.h"
class Map {
    public:
        Map(cs225::PNG& map);
        void addPoint(double lat, double lng);
        cs225::PNG& getMap();
    private:
        PNG map;
};