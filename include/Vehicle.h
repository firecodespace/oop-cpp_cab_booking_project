#ifndef VEHICLE_H
#define VEHICLE_H

#include <string>
using namespace std;

class Vehicle {
private:
    string model;
    string registrationNumber;
    string type; // Sedan, SUV, etc.

public:
    Vehicle();
    Vehicle(string model, string regNo, string type);
    ~Vehicle();
    
    // Getters
    string getModel() const { return model; }
    string getRegistrationNumber() const { return registrationNumber; }
    string getType() const { return type; }
    
    void displayVehicleInfo() const;
};

#endif
