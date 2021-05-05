#pragma once
#include <string>

class Airport {
 public:
  Airport();

  Airport(std::string code, double latitude, double longitude);

  std::string getCode() const;

  double getLatitude() const;

  double getLongitude() const;

  bool operator==(const Airport& rhs) const;

  bool operator<(const Airport& rhs) const;

 private:
  std::string code_;
  double latitude_;
  double longitude_;
};