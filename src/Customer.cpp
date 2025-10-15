#include "../include/Customer.h"
#include <iostream>

Customer::Customer() : Person(), totalRidesBooked(0) {
    currentLocation = Location(0, 0, "Default Location");
}

Customer::Customer(string name, string phone)
    : Person(name, phone), totalRidesBooked(0) {
    currentLocation = Location(0, 0, "Customer Location");
    cout << "Customer " << name << " registered" << endl;
}

Customer::~Customer() {
    cout << "Customer destructor called for " << name << endl;
}

void Customer::displayInfo() const {
    cout << "\n--- Customer Information ---" << endl;
    cout << "ID: " << id << endl;
    cout << "Name: " << name << endl;
    cout << "Phone: " << phoneNumber << endl;
    cout << "Total Rides: " << totalRidesBooked << endl;
}
