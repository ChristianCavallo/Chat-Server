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

    vector<Chat*> v;

    Chat* c10 = new Chat("");
    c10->Name = "Lista 10";
    c10->NumNotifications = 10;

    Chat* c2= new Chat("");
    c2->Name = "Lista 1";
    c2->NumNotifications = 1;

    Chat* c5= new Chat("");
    c5->Name = "Lista 0";
    c5->NumNotifications = 11;

    v.push_back(c10);
    v.push_back(c2);
    v.push_back(c5);

    sort(v.begin(), v.end(), [](const Chat* lhs, const Chat* rhs) {
        return lhs->NumNotifications > rhs->NumNotifications;
    });

    for(auto val : v){
        cout << val->Name << "\n";
    }


    auto *server = new Server();
    server->start();


    Dispatcher::getInstance().server = server;


    cin.get();

}