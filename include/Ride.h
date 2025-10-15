#ifndef RIDE_H
#define RIDE_H

#include "Customer.h"
#include "Driver.h"
#include "Location.h"
#include <string>

enum RideStatus {
    REQUESTED,
    ONGOING,
    COMPLETED,
    CANCELLED
};

class Ride {
private:
    int rideId;
    static int nextRideId;
    Customer* customer;
    Driver* driver;
    Location pickupLocation;
    Location destination;
    double distance;
    double fare;
    RideStatus status;

public:
    Ride();
    Ride(Customer* cust, Driver* drv, Location pickup, Location dest, double dist, double fare);
    ~Ride();
    
    // Getters
    int getRideId() const { return rideId; }
    Customer* getCustomer() const { return customer; }
    Driver* getDriver() const { return driver; }
    double getDistance() const { return distance; }
    double getFare() const { return fare; }
    RideStatus getStatus() const { return status; }
    Location getDestination() const { return destination; }
    
    // Setters
    void setStatus(RideStatus s) { status = s; }
    
    void displayRideInfo() const;
};

#endif
