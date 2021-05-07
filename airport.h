#pragma once

#include <string>

/** Represents the data of an Airport. */
class Airport {
 public:
  /** Default constructor. */
  Airport();

  /** 
   * Creates an Airport with the specified code and position.
   * @param code 3 letter airport code
   * @param latitude latitude of this airport
   * @param longitude longitude of this airport
   */
  Airport(const std::string& code, double latitude, double longitude);

  std::string getCode() const;
  double getLatitude() const;
  double getLongitude() const;

 private:
  std::string code_;
  double latitude_;
  double longitude_;
};