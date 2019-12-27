//
// Created by chryc on 14/12/2019.
//

#ifndef CHAT_SERVER_DISPATCHER_H
#define CHAT_SERVER_DISPATCHER_H


#include "../Socket/Client.h"
#include "../Managers/Users_Manager.h"

class Dispatcher {
public:
    static Dispatcher &getInstance() {
        static Dispatcher instance;
        return instance;
    }

private:
    //allora noe, il dispatcher deve avere un collegamento ai gestori. infatti avevo aggiunto questi TODO:
    //altrimenti che li abbiamo fatti a fare?

    //TODO: GESTORE CHAT ----> GestoreChat *gestoreChat;

    Users_Manager* usersManager;

    Dispatcher() {
        usersManager = new Users_Manager();
    }

public:
    Dispatcher(Dispatcher const &) = delete;

    void operator=(Dispatcher const &) = delete;

    //============================================
public:


    void executeRequest(Client &sender, string message);

    void executeResponse(Client &sender, Command *c);

};


#endif //CHAT_SERVER_DISPATCHER_H
