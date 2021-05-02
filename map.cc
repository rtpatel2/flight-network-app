#include "map.h"

Map::Map(PNG& map): map(map) {

}

void Map::addPoint(double lat, double lng) {
    int width = map.width();
    map.getPixel(0,0);
}

PNG& Map::getMap() {
    return map;
}