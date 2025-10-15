#include "../include/Location.h"
#include <iostream>
#include <cmath>

Location::Location() : latitude(0.0), longitude(0.0), address("Unknown") {}

Location::Location(double lat, double lon, string addr)
    : latitude(lat), longitude(lon), address(addr) {}

Location::~Location() {}

double Location::calculateDistance(const Location& loc1, const Location& loc2) {
    // Simplified distance calculation (in km)
    double latDiff = loc2.latitude - loc1.latitude;
    double lonDiff = loc2.longitude - loc1.longitude;
    return sqrt(latDiff * latDiff + lonDiff * lonDiff) * 111.0; // Approximate km conversion
}

void Location::displayLocation() const {
    cout << "Location: " << address << " (" << latitude << ", " << longitude << ")" << endl;
}
