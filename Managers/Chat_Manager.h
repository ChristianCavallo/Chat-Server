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

public:
    vector<Chat *> fetchChats(const string &id);

    Chat* addMessageToChat(const string &chatid, Message *m);

    Chat *createChat(Chat* ch);

};


#endif //CHAT_SERVER_CHAT_MANAGER_H
