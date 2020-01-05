//
// Created by chryc on 29/12/2019.
//

#include "Chat.h"


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




