// Server side C/C++ program to demonstrate Server programming

#include <iostream>
#include "Socket/Server.h"
#include "Socket/Crypto.h"
#include <string>
#include <mongoc.h>
#include <fstream>
#include "Utils/base64.h"
#include <iostream>
#include <thread>
#include "include/rapidjson/prettywriter.h"
#include "include/rapidjson/stringbuffer.h"
#include "include/rapidjson/document.h"
#include <sstream>
#include <iomanip>
#include "Commands/Command.h"

using namespace std;


int main() {

    Server *server = new Server();
    server->start();

    cin.get();

}