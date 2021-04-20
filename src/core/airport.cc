#include "core/airport.h"

#include <utility>
Airport::Airport(std::string code, double latitude, double longitude):code_(std::move(code)), latitude_(latitude), longitude_(longitude) {

}

std::string Airport::getCode() const {
    return code_;
}

double Airport::getLatitude() const {
    return latitude_;
}

double Airport::getLongitude() const {
    return longitude_;
}

