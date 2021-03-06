#include <utility>

#include "airport.h"

Airport::Airport() = default;

Airport::Airport(const std::string& code, double latitude, double longitude)
    : code_(code), latitude_(latitude), longitude_(longitude) {}

std::string Airport::getCode() const { return code_; }

double Airport::getLatitude() const { return latitude_; }

double Airport::getLongitude() const { return longitude_; }