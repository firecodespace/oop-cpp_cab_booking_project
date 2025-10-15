#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "Person.h"
#include "Location.h"

class Customer : public Person {
private:
    Location currentLocation;
    int totalRidesBooked;

public:
    Customer();
    Customer(string name, string phone);
    ~Customer() override;
    
    // Getters
    Location getCurrentLocation() const { return currentLocation; }
    int getTotalRidesBooked() const { return totalRidesBooked; }
    
    // Setters
    void setCurrentLocation(Location loc) { currentLocation = loc; }
    void incrementRidesBooked() { totalRidesBooked++; }
    
    // Override virtual function
    void displayInfo() const override;
};

#endif
