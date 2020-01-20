//
// Created by chryc on 29/12/2019.
//



#ifndef CHAT_SERVER_CHAT_MANAGER_H
#define CHAT_SERVER_CHAT_MANAGER_H

#include <vector>
#include <string>
#include <iostream>
#include "../Primitives/Chat.h"
#include "../Primitives/Message.h"

using namespace std;

class Chat_Manager {

public:
    vector<Chat *> fetchChats(const string &id);

    Chat* addMessageToChat(const string &chatid, Message *m);

    string createChat(Chat* ch);

    Chat *getChatById(const string &id);

    string deleteChat(const string &chatid, const string& userid);
};


#endif //CHAT_SERVER_CHAT_MANAGER_H
