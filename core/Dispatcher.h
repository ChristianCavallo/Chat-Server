//
// Created by chryc on 14/12/2019.
//

#ifndef CHAT_SERVER_DISPATCHER_H
#define CHAT_SERVER_DISPATCHER_H


#include "../Socket/Client.h"
#include "../Socket/Server.h"

class Dispatcher {
public:
    static Dispatcher &getInstance() {
        static Dispatcher instance;
        return instance;
    }

private:
    //TODO: GESTORE UTENTI -----> GestoreUtenti *gestoreUtenti;
    //TODO: GESTORE CHAT ----> GestoreChat *gestoreChat;



    Dispatcher() {}

public:

    Server *server;

    Dispatcher(Dispatcher const &) = delete;

    void operator=(Dispatcher const &) = delete;

    //============================================
public:


    void executeRequest(Client &sender, const string &message);

    void executeResponse(Client &sender, Command *c);

};


#endif //CHAT_SERVER_DISPATCHER_H
