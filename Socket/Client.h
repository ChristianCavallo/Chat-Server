//
// Created by chryc on 06/12/2019.
//


#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#pragma comment (lib, "Ws2_32.lib")

#include <Windows.h>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <thread>
#include <string>


#ifndef CHAT_SERVER_CLIENT_H
#define CHAT_SERVER_CLIENT_H


class Client {
private:
    SOCKET sck;
    void receive();
    std::thread t;
public:
    Client(){};
    Client(SOCKET &sck);

    bool closed = false;

    void setSocket(SOCKET &sck){ this->sck = sck; };

    void start();

    void close();

    void sendMessage(std::string msg);

    virtual ~Client();
};


#endif //CHAT_SERVER_CLIENT_H
