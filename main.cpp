// Server side C/C++ program to demonstrate Server programming

#include <iostream>
#include <string>
#include "Socket/Server.h"
#include "core/Dispatcher.h"

using namespace std;


int main() {

    auto *server = new Server();
    server->start();

    Dispatcher::getInstance().server = server;
    
    cin.get();

}