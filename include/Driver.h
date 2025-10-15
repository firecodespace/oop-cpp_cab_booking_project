#ifndef DRIVER_H
#define DRIVER_H

#include "Person.h"
#include "Vehicle.h"
#include "Location.h"

class Driver : public Person {
private:
    Vehicle* vehicle; // Composition - demonstrating has-a relationship
    double rating;
    bool isAvailable;
    Location currentLocation;

public:
    Driver();
    Driver(string name, string phone, Vehicle* veh, double rating);
    ~Driver() override;
    
    // Getters
    Vehicle* getVehicle() const { return vehicle; }
    double getRating() const { return rating; }
    bool getAvailability() const { return isAvailable; }
    Location getCurrentLocation() const { return currentLocation; }
    
    // Setters
    void setAvailability(bool available) { isAvailable = available; }
    void setCurrentLocation(Location loc) { currentLocation = loc; }
    void setRating(double r) { rating = r; }
    
    // Override virtual function
    void displayInfo() const override;
};

#endif
