#include "../include/CustomerManager.h"
#include <iostream>

CustomerManager* CustomerManager::instance = nullptr;

CustomerManager& CustomerManager::getInstance() {
    if (instance == nullptr) {
        instance = new CustomerManager();
    }
    return *instance;
}

void CustomerManager::addCustomer(Customer* customer) {
    customers.push_back(customer);
    cout << "Customer " << customer->getName() << " registered" << endl;
}

Customer* CustomerManager::findCustomerByName(string name) {
    for (Customer* customer : customers) {
        if (customer->getName() == name) {
            return customer;
        }
    }
    return nullptr;
}

void CustomerManager::displayAllCustomers() const {
    cout << "\n=== All Registered Customers ===" << endl;
    for (const Customer* customer : customers) {
        customer->displayInfo();
    }
}

CustomerManager::~CustomerManager() {
    for (Customer* customer : customers) {
        delete customer;
    }
    customers.clear();
}
