//
// Created by chryc on 29/12/2019.
//

#include "Chat_Manager.h"
#include "../Database/mongodb.h"
#include "../Database/MediaManager.h"

vector<Chat *> Chat_Manager::fetchChats(const string &id) {

    return Mongodb::getInstance().getChats(id);

}

//permette di inserire in base al chatid i messaggi di quella chat
Chat* Chat_Manager::addMessageToChat(const string &chatid, Message *m) {

    if(!m->Media.empty()){
        m->Media = MediaManager::saveMedia(m->Media);
    }

    return Mongodb::getInstance().updateMessage(chatid, m);

}


string Chat_Manager::createChat(Chat* ch) {

    return Mongodb::getInstance().CreateChat(ch);

}

Chat* Chat_Manager::getChatById(const string& id){

    return Mongodb::getInstance().getChatById(id);

}

string Chat_Manager::deleteChat(const string& chatid, const string& userid){

    Chat* ch = Mongodb::getInstance().getChatById(chatid);
    if(ch == nullptr){
        return "Chat doesn't exist.";
    }

    if(ch->IsGroup){

        return Mongodb::getInstance().deletePartecipant(chatid,userid);

    }

    if(find(ch->Participants.begin(), ch->Participants.end(), userid) == ch->Participants.end()){ //così non la trova se imposto invece == diverso allora lo trova
       delete ch;
       return "User doesn't partecipate to this chat";
    }

    return Mongodb::getInstance().deleteChatById(chatid);

}