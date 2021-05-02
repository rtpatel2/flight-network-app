#include "map.h"
#include "cs225/HSLAPixel.h"
#include <cmath>



Map::Map(PNG& map): map(map) {

}

void Map::addPoint(double lat, double lng) {
    //formula derived from:
    //https://stackoverflow.com/questions/14329691/convert-latitude-longitude-point-to-a-pixels-x-y-on-mercator-projection
    double width = map.width();
    double height = map.height();
    
    double x = (lng+180)*(width/360.0);
    double latRad = lat*M_PI/180.0;
    // double mercN = std::log(std::tan(M_PI/4)+(latRad/2));
        double mercN = std::log(std::tan(M_PI/4+latRad/2));

    double y = height/2 - (width*mercN/(2*M_PI));
    HSLAPixel red(0,1,0.5,1);


     //y = (y-450)*1.5+450;
    for(int i = (int)x-1; i<(int)x+1; i++) {
        for(int j = (int)y-1; j<(int)y+1; j++) {
              map.getPixel(i,j) = red;  
        }
    }

}

PNG& Map::getMap() {
    return map;
}