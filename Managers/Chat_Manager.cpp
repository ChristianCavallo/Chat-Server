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
        string mediaId= MediaManager::saveMedia(m->Media); //ritorna id del file cachato
        m->Media= mediaId;
    }

    return Mongodb::getInstance().updateMessage(chatid, m);

}


Chat *Chat_Manager::createChat(Chat* ch) {

    string result= Mongodb::getInstance().CreateChat(ch);
    //essendo che il controllo se esiste la chat è fatta nella funzione getchat che viene richiamata in addchat qua controllo
    //solo quello che ritorna chat.
    if(result=="ok"){

        return ch;
    }

    return nullptr;
}
