// Server side C/C++ program to demonstrate Server programming

#include <iostream>
#include <string>
#include "Database/mongodb.h"
#include "Socket/Server.h"
#include "Commands/Command.h"
#include "core/Dispatcher.h"


using namespace std;


int main() {

    Mongodb::getInstance(); //Prima inizializzazione del db
    Dispatcher::getInstance(); //Lazy initialization

    auto *server = new Server();
    server->start();

    Dispatcher::getInstance().server = server;

    cin.get();

}