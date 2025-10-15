#include "WebServer.h"
#include <iostream>

int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "   SMART RIDE BOOKING WEB SERVER" << std::endl;
    std::cout << "========================================" << std::endl;
    
    WebServer server;
    server.setupRoutes();
    server.start(8080);
    
    return 0;
}
