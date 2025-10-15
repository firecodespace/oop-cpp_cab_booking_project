#ifndef WEBSERVER_H
#define WEBSERVER_H

#include "lib/httplib.h"
#include "DriverManager.h"
#include "CustomerManager.h"
#include "RideManager.h"
#include <string>
#include <sstream>

class WebServer {
private:
    httplib::Server server;
    DriverManager* driverMgr;
    CustomerManager* customerMgr;
    RideManager* rideMgr;

public:
    WebServer();
    void setupRoutes();
    void start(int port = 8080);
    
private:
    std::string driversToJson();
    std::string customersToJson();
    std::string ridesToJson();
    std::string statsToJson();
    void handleAddDriver(const httplib::Request& req, httplib::Response& res);
    void handleAddCustomer(const httplib::Request& req, httplib::Response& res);
    void handleBookRide(const httplib::Request& req, httplib::Response& res);
};

#endif
