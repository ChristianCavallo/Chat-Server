// Server side C/C++ program to demonstrate Server programming

#include <iostream>
#include <string>
#include "Database/mongodb.h"
#include "Socket/Server.h"
#include "Commands/Command.h"
#include "core/Dispatcher.h"
#include "Database/MediaManager.h"
#include <fstream>

using namespace std;


int main() {


    string t = MediaManager::saveMedia("prova123prova!");
    string res = MediaManager::getMediaById(t);
    //cout << t << "\n";
    if (!res.empty()) {
        cout << res << "\n";
    }


    Dispatcher::getInstance(); //Lazy initialization

    auto *server = new Server();
    server->start();

    Dispatcher::getInstance().server = server;

    cin.get();

}