#include "../include/Vehicle.h"
#include <iostream>

Vehicle::Vehicle() : model("Unknown"), registrationNumber("N/A"), type("Sedan") {
    cout << "Vehicle default constructor called" << endl;
}

Vehicle::Vehicle(string model, string regNo, string type)
    : model(model), registrationNumber(regNo), type(type) {
    cout << "Vehicle created: " << model << endl;
}

Vehicle::~Vehicle() {
    cout << "Vehicle destructor called for " << model << endl;
}

void Vehicle::displayVehicleInfo() const {
    cout << "Vehicle: " << model << " (" << type << ") - " << registrationNumber << endl;
}
