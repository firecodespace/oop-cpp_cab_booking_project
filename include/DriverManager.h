#ifndef DRIVERMANAGER_H
#define DRIVERMANAGER_H

#include "Driver.h"
#include <vector>

// Singleton pattern
class DriverManager {
private:
    static DriverManager* instance;
    vector<Driver*> drivers;
    
    // Private constructor for Singleton
    DriverManager() {}
    
public:
    // Delete copy constructor and assignment operator
    DriverManager(const DriverManager&) = delete;
    DriverManager& operator=(const DriverManager&) = delete;
    
    static DriverManager& getInstance();
    
    void addDriver(Driver* driver);
    Driver* findAvailableDriver();
    void displayAllDrivers() const;
    vector<Driver*> getAllDrivers() const { return drivers; }
    
    ~DriverManager();
};

#endif
