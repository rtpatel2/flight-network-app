#pragma once
#include "cs225/PNG.h"
using namespace cs225;
class Map {
    public:
        Map(PNG& map);
        void addPoint(double lat, double lng);
        PNG& getMap();
    private:
        PNG map;
};