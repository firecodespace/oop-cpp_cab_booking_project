#ifndef RIDEMANAGER_H
#define RIDEMANAGER_H

#include "Ride.h"
#include "PricingStrategy.h"
#include <vector>

// Singleton pattern
class RideManager {
private:
    static RideManager* instance;
    vector<Ride*> rides;
    PricingStrategy* pricingStrategy;
    
    RideManager();
    
public:
    RideManager(const RideManager&) = delete;
    RideManager& operator=(const RideManager&) = delete;
    
    static RideManager& getInstance();
    
    void setPricingStrategy(PricingStrategy* strategy) { pricingStrategy = strategy; }
    Ride* bookRide(Customer* customer, Driver* driver, Location pickup, 
                   Location destination, double distance);
    void displayAllRides() const;
    int getActiveRidesCount() const;
    
    ~RideManager();
};

#endif
