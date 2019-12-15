// Server side C/C++ program to demonstrate Server programming

#include <iostream>
#include <string>
#include "Database/mongodb.h"
#include "Socket/Server.h"
#include "Commands/Command.h"
#include "core/Dispatcher.h"

using namespace std;


int main() {
    Dispatcher::getInstance(); //Lazy initialization

    Server *server = new Server();
    server->start();

    cin.get();

}