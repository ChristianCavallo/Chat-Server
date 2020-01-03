//
// Created by chryc on 07/12/2019.
//

#include <string>
#include <iostream>
#include <rapidjson/prettywriter.h>
#include <rapidjson/stringbuffer.h>
#include "../Primitives/User.h"
#include "../Primitives/Chat.h"
#include "../Utils/utils.h"

#ifndef CHAT_SERVER_COMMAND_H
#define CHAT_SERVER_COMMAND_H

#endif //CHAT_SERVER_COMMAND_H

using namespace std;
using namespace rapidjson;

enum Commands {
    COMMAND_TEST = -1,

    COMMAND_KEY_RESPONSE = 0,

    COMMAND_REGISTER_REQUEST = 10,
    COMMAND_REGISTER_RESPONSE = 11,

    COMMAND_LOGIN_REQUEST = 20,
    COMMAND_LOGIN_RESPONSE = 21,

    COMMAND_ADD_CONTACT_REQUEST = 30,
    COMMAND_ADD_CONTACT_RESPONSE = 31,

    COMMAND_MESSAGE_REQUEST = 40, //Utente invia un messaggio
    COMMAND_MESSAGE_RESPONSE = 41, //Utente riceve un messaggio

    COMMAND_CREATE_GROUP_REQUEST = 50,
    COMMAND_CREATE_GROUP_RESPONSE = 51,

    COMMAND_MEDIA_REQUEST = 60,
    COMMAND_MEDIA_RESPONSE = 61,

    COMMAND_DELETE_CHAT_REQUEST = 70,
    COMMAND_DELETE_CHAT_RESPONSE = 71,

    COMMAND_FETCH_CONTACTS_REQUEST = 80,
    COMMAND_FETCH_CONTACTS_RESPONSE = 81,

    COMMAND_FETCH_CHAT_REQUEST = 90,
    COMMAND_FETCH_CHAT_RESPONSE = 91

};

class Command {
public:
    int id;

    Command(int id) {
        this->id = id;
    }

    virtual ~Command() {}

    virtual string getSerializedString() {
        StringBuffer sb;
        PrettyWriter<StringBuffer> prettyWriter(sb);
        Serialize(prettyWriter);
        return sb.GetString();
    }

protected:

    virtual void Serialize(PrettyWriter <StringBuffer> &writer) const {
        writer.String("id");
        writer.Int(id);
    };


};

class CommandRegistration : public Command {

private:
    string result;
public:
    CommandRegistration(const string &result) : Command(COMMAND_REGISTER_RESPONSE), result(result) {}

    void Serialize(PrettyWriter <StringBuffer> &writer) const {
        //questo è il serializzatore, cioè  quello che crea l'oggetto json
        writer.StartObject();

        Command::Serialize(writer); //questo aggiunge "id" : 11
        writer.String("res");
        writer.String(result.c_str(), static_cast<SizeType>(result.size()));

        //Il padre ha il metodo che fa la stringa, la stessa cosa di python
        writer.EndObject();
    }

};

class CommandLogin : public Command {

private:
    User *u;

public:
    //Questo è il comando che dobbiamo mandare come response
    //Dove tutti i parametri che metti, saranno inseriti nel json...
    //in questo caso ci serve solo l'email e la password
    //l'id nn ci serve... xke sappiamo che la response ha id 23
    CommandLogin(User *u) : Command(COMMAND_LOGIN_RESPONSE) {
        this->u = u;
    }
    //ci sei con il costruttore? stiamo creando un comando con
    // l'id della response e ci stiamo aggiungendo il parametro email e password

    void Serialize(PrettyWriter <StringBuffer> &writer) const {
        //questo è il serializzatore, cioè  quello che crea l'oggetto json
        writer.StartObject();

        Command::Serialize(writer); //questo aggiunge "id" : 21
        writer.String("user-id");
        if(u == nullptr){
            writer.Null();
        } else {
            writer.String(u->id.c_str(), static_cast<SizeType>(u->id.size()));

            //cosa altro ci puo servire... nome... cognome... email?
            writer.String("name");
            writer.String(u->name.c_str(), static_cast<SizeType>(u->name.size()));

            writer.String("surname");
            writer.String(u->surname.c_str(), static_cast<SizeType>(u->surname.size()));
            //devo passare quello che interessa il python
        }
        //Il padre ha il metodo che fa la stringa, la stessa cosa di python
        writer.EndObject();
    }
};

class CommandKey : public Command {
private:
    string key_RSA;
    string key_AES_b64;
    string iv_AES_b64;

public:
    CommandKey(const string &keyRsa, const string &keyAesB64, const string &ivAesB64) : Command(COMMAND_KEY_RESPONSE),
                                                                                        key_RSA(keyRsa),
                                                                                        key_AES_b64(keyAesB64),
                                                                                        iv_AES_b64(ivAesB64) {};

    void Serialize(PrettyWriter<StringBuffer> &writer) const {
        writer.StartObject();

        Command::Serialize(writer);
        writer.String("key-RSA");
        writer.String(key_RSA.c_str(), static_cast<SizeType>(key_RSA.size()));

        writer.String("key-AES");
        writer.String(key_AES_b64.c_str(), static_cast<SizeType>(key_AES_b64.size()));

        writer.String("iv-AES");
        writer.String(iv_AES_b64.c_str(), static_cast<SizeType>(iv_AES_b64.size()));

        writer.EndObject();
    }

};

class CommandTest : public Command {
private:
    string message;
public:
    CommandTest(const string &message) : Command(COMMAND_TEST), message(message) {}

    void print() {
        std::cout << message << "\n";
    }

    void Serialize(PrettyWriter<StringBuffer> &writer) const {
        writer.StartObject();

        Command::Serialize(writer);
        writer.String("message");
        writer.String(message.c_str(), static_cast<SizeType>(message.size()));

        writer.EndObject();
    }

};

class CommandMedia : public Command {
private:
    string media_id;
    string media;
public:

    CommandMedia(const string &mediaId, const string &media) : Command(COMMAND_MEDIA_RESPONSE), media_id(mediaId),
                                                               media(media) {}

    void Serialize(PrettyWriter <StringBuffer> &writer) const {
        writer.StartObject();

        Command::Serialize(writer);
        writer.String("media-id");
        writer.String(media_id.c_str(), static_cast<SizeType>(media_id.size()));

        writer.String("media");
        if (media == "") {
            writer.Null();
        } else {
            writer.String(media.c_str(), static_cast<SizeType>(media.size()));
        }


        writer.EndObject();
    }

};

class CommandGeneric : public Command {
private:
    bool result;
    string content;
public:
    CommandGeneric(int id, bool result, const string &content) : Command(id), result(result), content(content) {}

    void Serialize(PrettyWriter <StringBuffer> &writer) const {
        writer.StartObject();

        Command::Serialize(writer);
        writer.String("result");
        writer.Bool(result);

        writer.String("content");
        writer.String(content.c_str(), static_cast<SizeType>(content.size()));

        writer.EndObject();
    }

};

class CommandFetchContacts: public Command {
private:

    vector<Chat*> ch;

public:

    CommandFetchContacts(const vector<Chat *> ch) : Command(COMMAND_FETCH_CONTACTS_RESPONSE), ch(ch) {}

    void Serialize(PrettyWriter <StringBuffer> &writer) const {
        writer.StartObject();

        Command::Serialize(writer);
        writer.String("chats");
        writer.StartArray();

        for(auto c: ch){
            writer.StartObject();

            writer.String("chat-id");
            writer.String(c->getId().c_str(), static_cast<SizeType>(c->getId().size()));

            writer.String("contact-id");
            writer.String(c->Participants.front().c_str(), static_cast<SizeType>(c->Participants.front().size()));

            writer.String("name");
            writer.String(c->Name.c_str(), static_cast<SizeType>(c->Name.size()));

            writer.String("isGroup");
            writer.Bool(c->IsGroup);

            writer.String("notifies");
            writer.Int(c->NumNotifications);

            writer.EndObject();
        }

        writer.EndArray();

        writer.EndObject();
    }

};

class CommandFetchChat: public Command {
private:
    vector<Message* > m;
    string status;

public:

    CommandFetchChat(const vector<Message *> m, string status) : Command(COMMAND_FETCH_CHAT_RESPONSE), m(m), status(status) {}

    void Serialize(PrettyWriter <StringBuffer> &writer) const {
        writer.StartObject();

        Command::Serialize(writer);
        writer.String("status");
        writer.String(status.c_str(), static_cast<SizeType>(status.size()));

        writer.String("messages");
        writer.StartArray();

        for(auto ms: m){
            writer.StartObject();

            writer.String("senderName");
            writer.String(ms->SenderName.c_str(), static_cast<SizeType>(ms->SenderName.size()));

            writer.String("sender_id");
            writer.String(ms->Sender_id.c_str(), static_cast<SizeType>(ms->Sender_id.size()));

            writer.String("time");
            string dt = utils::formatDateFromMilliseconds(ms->ReceptionDate);
            writer.String(dt.c_str(), static_cast<SizeType>(dt.size()));

            writer.String("content");
            writer.String(ms->Content.c_str(), static_cast<SizeType>(ms->Content.size()));

            writer.String("media");
            writer.String(ms->Media.c_str(), static_cast<SizeType>(ms->Media.size()));

            writer.EndObject();
        }

        writer.EndArray();

        writer.EndObject();
    }

};


class CommandMessage: public Command {
private:
    string chatid;
    Message* m;

public:

    CommandMessage(const string &chatid, Message *m) : Command(COMMAND_MESSAGE_RESPONSE), chatid(chatid), m(m) {}

    void Serialize(PrettyWriter <StringBuffer> &writer) const {
        writer.StartObject();

        Command::Serialize(writer);
        writer.String("chat-id");
        writer.String(chatid.c_str(), static_cast<SizeType>(chatid.size()));


        writer.String("senderName");
        writer.String(m->SenderName.c_str(), static_cast<SizeType>(m->SenderName.size()));

        writer.String("sender_id");
        writer.String(m->Sender_id.c_str(), static_cast<SizeType>(m->Sender_id.size()));

        writer.String("time");
        string dt = utils::formatDateFromMilliseconds(m->ReceptionDate);
        writer.String(dt.c_str(), static_cast<SizeType>(dt.size()));

        writer.String("content");
        writer.String(m->Content.c_str(), static_cast<SizeType>(m->Content.size()));

        writer.String("media");
        writer.String(m->Media.c_str(), static_cast<SizeType>(m->Media.size()));

        writer.EndObject();
    }

};