//
// Created by chryc on 29/12/2019.
//

#ifndef CHAT_SERVER_CHAT_H
#define CHAT_SERVER_CHAT_H

#include <string>
#include <list>
#include <vector>
#include "Message.h"

using namespace std;

class Chat {
private:

public:
    string Id;
    string Name;
    list<string> Participants; //lista di id user
    bool IsGroup; //per capire se la chat è un gruppo o chat singola
    vector<Message *> messagges;

    int NumNotifications; //non considerato nel mongo ma gestito nel server

    Chat::Chat(const string &id) : Id(id) {}


    void addPartecipant(const string &id) {
        Participants.push_front(id);
    }

    void addMessage(Message *m) {
        messagges.push_back(m);
    }

    virtual ~Chat();

    bool operator<(const Chat &rhs) const;

};


#endif //CHAT_SERVER_CHAT_H
