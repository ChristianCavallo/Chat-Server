// Server side C/C++ program to demonstrate Server programming

#include <iostream>
#include <string>
#include "Database/mongodb.h"
#include "Socket/Server.h"
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>

using namespace std;


int main() {

    Mongodb *mongo = new Mongodb();
    mongo->CreateCollection("lista");


    Server *server = new Server();
    server->start();

    cin.get();

}