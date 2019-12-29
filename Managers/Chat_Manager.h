//
// Created by chryc on 29/12/2019.
//

#include <vector>
#include <string>
#include <iostream>
#include "../Primitives/Chat.h"
#include "../Primitives/Message.h"

#ifndef CHAT_SERVER_CHAT_MANAGER_H
#define CHAT_SERVER_CHAT_MANAGER_H

using namespace std;

class Chat_Manager {

    vector<Chat *> fetchChats(const string &id);

    void addMessageToChat(const string &chatid, Message *m);

    Chat *createChat(vector<string> ids);

};


#endif //CHAT_SERVER_CHAT_MANAGER_H
