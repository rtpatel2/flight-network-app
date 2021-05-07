#include "map.h"
#include "cs225/HSLAPixel.h"
#include <cmath>
#include <queue>
#include <set>
#include <utility>
#include <iostream>

Map::Map(const cs225::PNG& map): map_(map) {}

void Map::AddPoint(double lat, double lng, double luminance) {
    std::pair<double, double> projection = ProjectMercator(lat, lng);
    double x = projection.first;
    double y = projection.second;

    cs225::HSLAPixel pixel_color(265, 1, luminance, 1);
    for (int i = max(0, (int) x - 1); i < min((int) map_.width(), (int) x + 1); ++i) {
        for (int j = max(0, (int) y - 1); j < min((int) map_.height(), (int) y + 1); ++j) {
            map_.getPixel(i,j) = pixel_color;  
        }
    }
}

void Map::Animate(const FlightGraph& graph,  AirportMap& airports, const std::string& origin, const std::string& gif_filename, const std::string& png_filename){
    Animation animation;
    cs225::PNG temp = cs225::PNG(map_);
    animation.addFrame(temp);

    int last_seen_degree = -1;

    std::queue<std::pair<std::string, int>> queue;
    std::set<std::string> visited;
    visited.insert(origin);
    queue.emplace(origin, 0);

    while (!queue.empty()) {
        std::string curr = queue.front().first;
        int curr_degree = queue.front().second;

        AddPoint(airports.at(curr).getLatitude(), airports.at(curr).getLongitude(), fmin(0.25 + (last_seen_degree + 1) * 0.15, 1.0));

        if (curr_degree != last_seen_degree) {
            last_seen_degree = curr_degree;
            cs225::PNG temp = cs225::PNG(map_);
            animation.addFrame(temp);
        }   
        queue.pop();

        for (auto& it: graph.at(curr)) {
            if (visited.count(it.first) == 0) {
                queue.emplace(it.first, curr_degree + 1);
                visited.insert(it.first);
            }
        }
    }

    animation.write(gif_filename);

    cs225::PNG lastFrame = animation.getFrame(animation.frameCount() - 1);
 	lastFrame.writeToFile(png_filename);
}

std::pair<double, double> Map::ProjectMercator(double lat, double lng) {
    double width = map_.width();
    double height = map_.height();

    // formula derived from:
    // https://stackoverflow.com/questions/14329691/convert-latitude-longitude-point-to-a-pixels-x-y-on-mercator-projection

    double x = (lng+180)*(width/360.0);
    double latRad = lat*M_PI/180.0;
    double mercN = std::log(std::tan(M_PI/4+latRad/2));

    double y = height/2 - (width*mercN/(2*M_PI));

    return std::make_pair(x, y);
}

cs225::PNG& Map::GetMap() {
    return map_;
}