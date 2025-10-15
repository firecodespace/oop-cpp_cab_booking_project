#include "WebServer.h"
#include <iostream>

WebServer::WebServer() {
    driverMgr = &DriverManager::getInstance();
    customerMgr = &CustomerManager::getInstance();
    rideMgr = &RideManager::getInstance();
    
    // Initialize sample data
    Vehicle* v1 = new Vehicle("Swift", "DL01AB1234", "Sedan");
    Driver* d1 = new Driver("Rohit", "9876543210", v1, 4.8);
    driverMgr->addDriver(d1);
    
    Vehicle* v2 = new Vehicle("Innova", "DL02CD5678", "SUV");
    Driver* d2 = new Driver("Amit", "9876543211", v2, 4.5);
    driverMgr->addDriver(d2);
    
    Customer* c1 = new Customer("Aditya", "9123456789");
    customerMgr->addCustomer(c1);
    
    Customer* c2 = new Customer("Priya", "9123456788");
    customerMgr->addCustomer(c2);
}

void WebServer::setupRoutes() {
    // Serve frontend files
    server.set_mount_point("/", "./frontend");
    
    // Enable CORS
    server.set_pre_routing_handler([](const httplib::Request& req, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Methods", "GET, POST, OPTIONS");
        res.set_header("Access-Control-Allow-Headers", "Content-Type");
        return httplib::Server::HandlerResponse::Unhandled;
    });
    
    // API Routes
    server.Get("/api/drivers", [this](const httplib::Request& req, httplib::Response& res) {
        res.set_content(driversToJson(), "application/json");
    });
    
    server.Get("/api/customers", [this](const httplib::Request& req, httplib::Response& res) {
        res.set_content(customersToJson(), "application/json");
    });
    
    server.Get("/api/rides", [this](const httplib::Request& req, httplib::Response& res) {
        res.set_content(ridesToJson(), "application/json");
    });
    
    server.Get("/api/stats", [this](const httplib::Request& req, httplib::Response& res) {
        res.set_content(statsToJson(), "application/json");
    });
    
    server.Post("/api/drivers", [this](const httplib::Request& req, httplib::Response& res) {
        handleAddDriver(req, res);
    });
    
    server.Post("/api/customers", [this](const httplib::Request& req, httplib::Response& res) {
        handleAddCustomer(req, res);
    });
    
    server.Post("/api/rides", [this](const httplib::Request& req, httplib::Response& res) {
        handleBookRide(req, res);
    });
}

std::string WebServer::driversToJson() {
    auto drivers = driverMgr->getAllDrivers();
    std::ostringstream json;
    json << "[";
    for (size_t i = 0; i < drivers.size(); i++) {
        if (i > 0) json << ",";
        json << "{"
             << "\"id\":" << drivers[i]->getId() << ","
             << "\"name\":\"" << drivers[i]->getName() << "\","
             << "\"phone\":\"" << drivers[i]->getPhoneNumber() << "\","
             << "\"vehicle\":\"" << drivers[i]->getVehicle()->getModel() << "\","
             << "\"rating\":" << drivers[i]->getRating() << ","
             << "\"available\":" << (drivers[i]->getAvailability() ? "true" : "false")
             << "}";
    }
    json << "]";
    return json.str();
}

std::string WebServer::customersToJson() {
    auto customers = customerMgr->getAllCustomers();
    std::ostringstream json;
    json << "[";
    for (size_t i = 0; i < customers.size(); i++) {
        if (i > 0) json << ",";
        json << "{"
             << "\"name\":\"" << customers[i]->getName() << "\","
             << "\"phone\":\"" << customers[i]->getPhoneNumber() << "\","
             << "\"totalRides\":" << customers[i]->getTotalRidesBooked()
             << "}";
    }
    json << "]";
    return json.str();
}

std::string WebServer::ridesToJson() {
    return "[{\"id\":1000,\"customer\":\"Aditya\",\"driver\":\"Rohit\",\"destination\":\"Connaught Place\",\"distance\":8.5,\"fare\":238.5,\"status\":\"completed\"}]";
}

std::string WebServer::statsToJson() {
    auto drivers = driverMgr->getAllDrivers();
    auto customers = customerMgr->getAllCustomers();
    int activeRides = rideMgr->getActiveRidesCount();
    
    std::ostringstream json;
    json << "{"
         << "\"totalDrivers\":" << drivers.size() << ","
         << "\"totalCustomers\":" << customers.size() << ","
         << "\"activeRides\":" << activeRides << ","
         << "\"totalRevenue\":1500.75"
         << "}";
    return json.str();
}

void WebServer::handleAddDriver(const httplib::Request& req, httplib::Response& res) {
    res.set_content("{\"success\":true,\"message\":\"Driver added\"}", "application/json");
}

void WebServer::handleAddCustomer(const httplib::Request& req, httplib::Response& res) {
    res.set_content("{\"success\":true,\"message\":\"Customer added\"}", "application/json");
}

void WebServer::handleBookRide(const httplib::Request& req, httplib::Response& res) {
    auto customer = customerMgr->getAllCustomers()[0];
    auto driver = driverMgr->findAvailableDriver();
    
    Location pickup(28.6139, 77.2090, "Pickup");
    Location dest(28.7041, 77.1025, "Destination");
    
    Ride* ride = rideMgr->bookRide(customer, driver, pickup, dest, 8.5);
    
    std::ostringstream json;
    json << "{"
         << "\"success\":true,"
         << "\"rideId\":" << ride->getRideId() << ","
         << "\"driver\":\"" << driver->getName() << "\","
         << "\"fare\":" << ride->getFare()
         << "}";
    
    res.set_content(json.str(), "application/json");
}

void WebServer::start(int port) {
    std::cout << "🚀 Server starting on http://localhost:" << port << std::endl;
    server.listen("0.0.0.0", port);
}
