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

bool Chat::operator<(const Chat &rhs) const {
    return NumNotifications < rhs.NumNotifications;
}

bool Chat::operator>(const Chat &rhs) const {
    return rhs < *this;
}

bool Chat::operator<=(const Chat &rhs) const {
    return !(rhs < *this);
}

bool Chat::operator>=(const Chat &rhs) const {
    return !(*this < rhs);
}


