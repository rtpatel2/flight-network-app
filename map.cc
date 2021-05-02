#include "map.h"

Map::Map(cs225::PNG& map): map(map) {

}

void Map::addPoint(double lat, double lng) {
    int width = map.width();
    map.getPixel(0,0);
}

cs225::PNG& Map::getMap() {
    return map;
}