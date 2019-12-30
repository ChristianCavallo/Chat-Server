//
// Created by chryc on 06/12/2019.
//

#include "Client.h"
#include <vector>
#include <thread>
#ifndef CHAT_SERVER_SERVER_H
#define CHAT_SERVER_SERVER_H


class Server {
private:
    bool stopFlag;
    std::vector<Client*> clients;
    std::thread t;

    void startListen();


public:
    Server();

    void start();
    void stop();

    Client *getClientByUserId(string id);
};


#endif //CHAT_SERVER_SERVER_H
