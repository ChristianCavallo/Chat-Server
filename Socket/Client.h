//
// Created by chryc on 06/12/2019.
//



#ifndef CHAT_SERVER_CLIENT_H
#define CHAT_SERVER_CLIENT_H

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#pragma comment (lib, "Ws2_32.lib")

#include <Windows.h>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include "Security/Crypto.h"
#include "../Primitives/User.h"
#include <iostream>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/document.h>


#include "../Commands/Command.h"

#include <thread>
#include <string>

class Client {
private:
    SOCKET sck;

    void receive();

    std::thread t;
    Crypto *crypto;
    bool cryptedRSA = false;
    bool cryptedAES = false;


public:
    int id;

    User* myUser;

    Client(SOCKET &sck);

    bool closed = false;

    void sendMessage(const std::string &msg);

    void start();

    void close();

    virtual ~Client();
};


#endif //CHAT_SERVER_CLIENT_H
