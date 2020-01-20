//
// Created by chryc on 06/12/2019.
//


#ifndef CHAT_SERVER_SERVER_H
#define CHAT_SERVER_SERVER_H

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#pragma comment (lib, "Ws2_32.lib")

#include <Windows.h>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <cstdio>
#include <string>
#include <iostream>
#include <vector>
#include <thread>
#include "Client.h"

#define DEFAULT_PORT "15000"

class Server {
private:
    bool stopFlag;
    std::vector<Client *> clients;
    std::thread t;

    void startListen();


public:
    Server();

    void start();

    void stop();

    Client *getClientById(int id);

    Client *getClientByUserId(string id);
};


#endif //CHAT_SERVER_SERVER_H
