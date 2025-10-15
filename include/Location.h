#ifndef LOCATION_H
#define LOCATION_H

#include <string>
using namespace std;

class Location {
private:
    double latitude;
    double longitude;
    string address;

public:
    Location();
    Location(double lat, double lon, string addr);
    ~Location();
    
    double getLatitude() const { return latitude; }
    double getLongitude() const { return longitude; }
    string getAddress() const { return address; }
    
    // Calculate distance between two locations
    static double calculateDistance(const Location& loc1, const Location& loc2);
    
    void displayLocation() const;
};

#endif
