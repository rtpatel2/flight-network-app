#pragma once
#include <string>

class Airport{
public:
    Airport(std::string code, double latitude, double longitude);
    std::string getCode() const;
    double getLatitude() const;
    double getLongitude() const;
private:
    std::string code_;
    double latitude_;
    double longitude_;
};

template <>
struct std::hash<Airport> {
    size_t operator()(const Airport &a) const {
        return (std::hash<std::string>()(a.getCode()));
    }
};