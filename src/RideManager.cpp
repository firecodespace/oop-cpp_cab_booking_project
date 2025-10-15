#include "../include/RideManager.h"
#include <iostream>

RideManager* RideManager::instance = nullptr;

RideManager::RideManager() {
    pricingStrategy = new DefaultPricing(); // Default strategy
}

RideManager& RideManager::getInstance() {
    if (instance == nullptr) {
        instance = new RideManager();
    }
    return *instance;
}

Ride* RideManager::bookRide(Customer* customer, Driver* driver, Location pickup,
                            Location destination, double distance) {
    double baseRate = 50.0;
    double fare = pricingStrategy->calculateFare(distance, baseRate);
    
    Ride* ride = new Ride(customer, driver, pickup, destination, distance, fare);
    rides.push_back(ride);
    
    driver->setAvailability(false);
    customer->incrementRidesBooked();
    
    return ride;
}

void RideManager::displayAllRides() const {
    cout << "\n=== All Rides ===" << endl;
    for (const Ride* ride : rides) {
        ride->displayRideInfo();
    }
}

int RideManager::getActiveRidesCount() const {
    int count = 0;
    for (const Ride* ride : rides) {
        if (ride->getStatus() == ONGOING) {
            count++;
        }
    }
    return count;
}

RideManager::~RideManager() {
    delete pricingStrategy;
    for (Ride* ride : rides) {
        delete ride;
    }
    rides.clear();
}
