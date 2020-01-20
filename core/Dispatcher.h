//
// Created by chryc on 14/12/2019.
//

#ifndef CHAT_SERVER_DISPATCHER_H
#define CHAT_SERVER_DISPATCHER_H


#include "../Primitives/User.h"

#include "../Managers/Users_Manager.h"
#include "../Managers/Chat_Manager.h"
#include "../Database/MediaManager.h"

#include <rapidjson/prettywriter.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/document.h>
#include "../Socket/Server.h"

class Dispatcher {
public:
    static Dispatcher &getInstance() {
        static Dispatcher instance;
        return instance;
    }

private:

    Chat_Manager* chatManager;
    Users_Manager* usersManager;

    Dispatcher() {
        usersManager = new Users_Manager();
        chatManager = new Chat_Manager();
    }

public:
    Server *server;

    Dispatcher(Dispatcher const &) = delete;

    void operator=(Dispatcher const &) = delete;


public:


    void executeRequest(Client &sender, const string &message);

    void logoutUser(const string &id);

    string getUserStatus(const string &user_id);

    int getNotifiesCount(vector<Message *> mv, bsoncxx::types::b_date lastaccess);
};


#endif //CHAT_SERVER_DISPATCHER_H
