#include "map.h"
#include "cs225/HSLAPixel.h"
#include <cmath>
#include <queue>
#include <set>
#include <iostream>
typedef std::unordered_map<std::string, std::unordered_map<std::string, double>> FlightGraph;


Map::Map(cs225::PNG& map): map(map) {

}

void Map::AddPoint(double lat, double lng) {
    //formula derived from:
    //https://stackoverflow.com/questions/14329691/convert-latitude-longitude-point-to-a-pixels-x-y-on-mercator-projection
    double width = map.width();
    double height = map.height();
    
    double x = (lng+180)*(width/360.0);
    double latRad = lat*M_PI/180.0;
    // double mercN = std::log(std::tan(M_PI/4)+(latRad/2));
        double mercN = std::log(std::tan(M_PI/4+latRad/2));

    double y = height/2 - (width*mercN/(2*M_PI));
    cs225::HSLAPixel red(0,1,0.5,1);


     //y = (y-450)*1.5+450;
    for(int i = (int)x-1; i<(int)x+1; i++) {
        for(int j = (int)y-1; j<(int)y+1; j++) {
              map.getPixel(i,j) = red;  
        }
    }
}


void Map::Animate(const FlightGraph& graph,  AirportList& airports, const std::string& origin, std::string& filename){
    Animation animation;
    std::queue<std::string> queue;
    std::set<std::string> visited;
    visited.insert(origin);
    queue.push(origin);
    int num = 0;
    while(!queue.empty()) {
        std::string curr = queue.front();
        AddPoint(airports.at(curr).getLatitude(), airports.at(curr).getLongitude());
        num++;
        //std::cout<<num<<std::endl;
        if(num%50==0) {
            cs225::PNG temp = cs225::PNG(map);
          animation.addFrame(temp);
        }
        //std::cout<<curr<<std::endl;
        queue.pop();

        for(auto& it: graph.at(curr)) {
            if(visited.count(it.first)==0) {
                queue.push(it.first);

                visited.insert(it.first);
            }
        }

    }
    animation.write(filename);
}

cs225::PNG& Map::GetMap() {
    return map;
}