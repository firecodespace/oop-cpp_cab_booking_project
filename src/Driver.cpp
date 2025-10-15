#include "../include/Driver.h"
#include <iostream>

Driver::Driver() : Person(), vehicle(nullptr), rating(5.0), isAvailable(true) {
    currentLocation = Location(0, 0, "Default Location");
}

Driver::Driver(string name, string phone, Vehicle* veh, double rating)
    : Person(name, phone), vehicle(veh), rating(rating), isAvailable(true) {
    currentLocation = Location(0, 0, "Starting Point");
    cout << "Driver " << name << " registered with rating " << rating << endl;
}

Driver::~Driver() {
    cout << "Driver destructor called for " << name << endl;
    delete vehicle; // Clean up dynamically allocated vehicle
}

void Driver::displayInfo() const {
    cout << "\n--- Driver Information ---" << endl;
    cout << "ID: " << id << endl;
    cout << "Name: " << name << endl;
    cout << "Phone: " << phoneNumber << endl;
    cout << "Rating: " << rating << "/5.0" << endl;
    cout << "Status: " << (isAvailable ? "Available" : "Busy") << endl;
    if (vehicle) {
        vehicle->displayVehicleInfo();
    }
}
