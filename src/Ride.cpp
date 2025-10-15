#include "../include/Ride.h"
#include <iostream>

int Ride::nextRideId = 1000;

Ride::Ride() : rideId(nextRideId++), customer(nullptr), driver(nullptr),
               distance(0.0), fare(0.0), status(REQUESTED) {}

Ride::Ride(Customer* cust, Driver* drv, Location pickup, Location dest, double dist, double fare)
    : rideId(nextRideId++), customer(cust), driver(drv), pickupLocation(pickup),
      destination(dest), distance(dist), fare(fare), status(ONGOING) {}

Ride::~Ride() {
    cout << "Ride destructor called for Ride ID: " << rideId << endl;
}

void Ride::displayRideInfo() const {
    cout << "\n--- Ride Information ---" << endl;
    cout << "Ride ID: " << rideId << endl;
    if (customer) {
        cout << "Customer: " << customer->getName() << endl;
    }
    if (driver) {
        cout << "Driver: " << driver->getName() << endl;
        cout << "Vehicle: " << driver->getVehicle()->getModel() << endl;
        cout << "Driver Rating: " << driver->getRating() << endl;
    }
    cout << "Destination: " << destination.getAddress() << endl;
    cout << "Distance: " << distance << " km" << endl;
    cout << "Fare: ₹" << fare << endl;
    
    string statusStr;
    switch(status) {
        case REQUESTED: statusStr = "Requested"; break;
        case ONGOING: statusStr = "Ongoing"; break;
        case COMPLETED: statusStr = "Completed"; break;
        case CANCELLED: statusStr = "Cancelled"; break;
    }
    cout << "Status: " << statusStr << endl;
}
