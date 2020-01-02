//
// Created by chryc on 29/12/2019.
//

#include "Chat.h"


int Chat::getNumNotifications() const {
    return NumNotifications;
}

const string &Chat::getId() const {
    return Id;
}

Chat::~Chat() {

    for(auto m : messagges){

        delete m;

    }
    messagges.clear();

    Participants.clear();

}


