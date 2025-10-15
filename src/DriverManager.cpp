#include "../include/DriverManager.h"
#include <iostream>

DriverManager* DriverManager::instance = nullptr;

DriverManager& DriverManager::getInstance() {
    if (instance == nullptr) {
        instance = new DriverManager();
    }
    return *instance;
}

void DriverManager::addDriver(Driver* driver) {
    drivers.push_back(driver);
    cout << "Driver " << driver->getName() << " added to system" << endl;
}

Driver* DriverManager::findAvailableDriver() {
    for (Driver* driver : drivers) {
        if (driver->getAvailability()) {
            return driver;
        }
    }
    return nullptr;
}

void DriverManager::displayAllDrivers() const {
    cout << "\n=== All Registered Drivers ===" << endl;
    for (const Driver* driver : drivers) {
        driver->displayInfo();
    }
}

DriverManager::~DriverManager() {
    for (Driver* driver : drivers) {
        delete driver;
    }
    drivers.clear();
}
