#ifndef CUSTOMERMANAGER_H
#define CUSTOMERMANAGER_H

#include "Customer.h"
#include <vector>

// Singleton pattern
class CustomerManager {
private:
    static CustomerManager* instance;
    vector<Customer*> customers;
    
    CustomerManager() {}
    
public:
    CustomerManager(const CustomerManager&) = delete;
    CustomerManager& operator=(const CustomerManager&) = delete;
    
    static CustomerManager& getInstance();
    
    void addCustomer(Customer* customer);
    Customer* findCustomerByName(string name);
    void displayAllCustomers() const;
    vector<Customer*> getAllCustomers() const { return customers; }
    
    ~CustomerManager();
};

#endif
