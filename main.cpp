#include <iostream>
#include "include/DriverManager.h"
#include "include/CustomerManager.h"
#include "include/RideManager.h"
#include "include/PricingStrategy.h"

using namespace std;

void displayMenu() {
    cout << "\n\n========================================" << endl;
    cout << "   SMART RIDE BOOKING SYSTEM" << endl;
    cout << "========================================" << endl;
    cout << "1. Add Driver" << endl;
    cout << "2. Add Customer" << endl;
    cout << "3. Book Ride" << endl;
    cout << "4. Display All Rides" << endl;
    cout << "5. Display All Drivers" << endl;
    cout << "6. Display All Customers" << endl;
    cout << "7. Change Pricing Strategy" << endl;
    cout << "8. Exit" << endl;
    cout << "========================================" << endl;
    cout << "Enter choice: ";
}

int main() {
    DriverManager& driverMgr = DriverManager::getInstance();
    CustomerManager& customerMgr = CustomerManager::getInstance();
    RideManager& rideMgr = RideManager::getInstance();
    
    int choice;
    
    // Add some default data
    cout << "\n--- Initializing System with Sample Data ---\n" << endl;
    
    // Add sample drivers
    Vehicle* v1 = new Vehicle("Swift", "DL01AB1234", "Sedan");
    Driver* d1 = new Driver("Rohit", "9876543210", v1, 4.8);
    driverMgr.addDriver(d1);
    
    Vehicle* v2 = new Vehicle("Innova", "DL02CD5678", "SUV");
    Driver* d2 = new Driver("Amit", "9876543211", v2, 4.5);
    driverMgr.addDriver(d2);
    
    // Add sample customers
    Customer* c1 = new Customer("Aditya", "9123456789");
    customerMgr.addCustomer(c1);
    
    Customer* c2 = new Customer("Priya", "9123456788");
    customerMgr.addCustomer(c2);
    
    while (true) {
        displayMenu();
        cin >> choice;
        cin.ignore(); // Clear input buffer
        
        switch (choice) {
            case 1: {
                // Add Driver
                string name, phone, model, regNo, type;
                double rating;
                
                cout << "\nEnter Driver Name: ";
                getline(cin, name);
                cout << "Enter Phone Number: ";
                getline(cin, phone);
                cout << "Enter Vehicle Model: ";
                getline(cin, model);
                cout << "Enter Registration Number: ";
                getline(cin, regNo);
                cout << "Enter Vehicle Type (Sedan/SUV/Bike): ";
                getline(cin, type);
                cout << "Enter Driver Rating (0-5): ";
                cin >> rating;
                
                Vehicle* vehicle = new Vehicle(model, regNo, type);
                Driver* driver = new Driver(name, phone, vehicle, rating);
                driverMgr.addDriver(driver);
                
                cout << "\n✓ Driver added successfully!" << endl;
                break;
            }
            
            case 2: {
                // Add Customer
                string name, phone;
                
                cout << "\nEnter Customer Name: ";
                getline(cin, name);
                cout << "Enter Phone Number: ";
                getline(cin, phone);
                
                Customer* customer = new Customer(name, phone);
                customerMgr.addCustomer(customer);
                
                cout << "\n✓ Customer registered successfully!" << endl;
                break;
            }
            
            case 3: {
                // Book Ride
                string customerName, destination;
                double distance;
                
                cout << "\nEnter Customer Name: ";
                getline(cin, customerName);
                
                Customer* customer = customerMgr.findCustomerByName(customerName);
                if (!customer) {
                    cout << "❌ Customer not found!" << endl;
                    break;
                }
                
                Driver* driver = driverMgr.findAvailableDriver();
                if (!driver) {
                    cout << "❌ No drivers available at the moment!" << endl;
                    break;
                }
                
                cout << "Enter Destination: ";
                getline(cin, destination);
                cout << "Enter Distance (km): ";
                cin >> distance;
                
                Location pickup(28.6139, 77.2090, "Current Location");
                Location dest(28.7041, 77.1025, destination);
                
                cout << "\n--- Booking Ride ---" << endl;
                cout << "Customer: " << customer->getName() << " -> Destination: " << destination << endl;
                
                Ride* ride = rideMgr.bookRide(customer, driver, pickup, dest, distance);
                
                cout << "Assigned Driver: " << driver->getName() 
                     << " (Vehicle: " << driver->getVehicle()->getModel()
                     << ", Rating: " << driver->getRating() << ")" << endl;
                cout << "Ride Distance: " << distance << " km" << endl;
                cout << "Fare: ₹" << ride->getFare() << endl;
                cout << "\nTotal Active Rides: " << rideMgr.getActiveRidesCount() << endl;
                cout << "\n✓ Ride booked successfully!" << endl;
                
                break;
            }
            
            case 4: {
                // Display All Rides
                rideMgr.displayAllRides();
                cout << "\nTotal Active Rides: " << rideMgr.getActiveRidesCount() << endl;
                break;
            }
            
            case 5: {
                // Display All Drivers
                driverMgr.displayAllDrivers();
                break;
            }
            
            case 6: {
                // Display All Customers
                customerMgr.displayAllCustomers();
                break;
            }
            
            case 7: {
                // Change Pricing Strategy
                int strategyChoice;
                cout << "\n--- Select Pricing Strategy ---" << endl;
                cout << "1. Default Pricing" << endl;
                cout << "2. Surge Pricing (1.5x)" << endl;
                cout << "3. Rating-Based Pricing" << endl;
                cout << "Enter choice: ";
                cin >> strategyChoice;
                
                PricingStrategy* strategy = nullptr;
                switch (strategyChoice) {
                    case 1:
                        strategy = new DefaultPricing();
                        break;
                    case 2:
                        strategy = new SurgePricing(1.5);
                        break;
                    case 3:
                        strategy = new RatingBasedPricing(4.5);
                        break;
                    default:
                        cout << "Invalid choice!" << endl;
                        continue;
                }
                
                rideMgr.setPricingStrategy(strategy);
                cout << "✓ Pricing strategy updated!" << endl;
                break;
            }
            
            case 8: {
                cout << "\n👋 Thank you for using Smart Ride Booking System!" << endl;
                cout << "Exiting..." << endl;
                return 0;
            }
            
            default:
                cout << "❌ Invalid choice! Please try again." << endl;
        }
    }
    
    return 0;
}
