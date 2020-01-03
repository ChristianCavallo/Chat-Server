//
// Created by chryc on 14/12/2019.
//
#include <rapidjson/prettywriter.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/document.h>
#include "../Commands/Command.h"
#include "../Database/MediaManager.h"
#include "../Primitives/User.h"
#include "Dispatcher.h"


void Dispatcher::executeRequest(Client &sender, const string &message) {
    Document document;

    document.Parse(message.c_str());

    Command *c;


    if (!document.HasMember("id")) {
        cout << "Invalid message received: " << message << "\n";
        return;
    }

    int id = document["id"].GetInt();
    User *u;
    vector<Chat *> chats;
    Chat *ch;
    Message *m;
    string result;
    Client *c1;
    switch (id) {
        case COMMAND_TEST:
            c = new CommandTest(document["message"].GetString());
            sender.sendMessage(c->getSerializedString());
            delete c;
            break;

        case COMMAND_REGISTER_REQUEST:

            u = new User("", document["name"].GetString(), document["surname"].GetString(),
                         document["email"].GetString(), document["password"].GetString());
            c = new CommandRegistration(usersManager->Registration(u));
            sender.sendMessage(c->getSerializedString());
            delete u;
            delete c;
            break;

        case COMMAND_LOGIN_REQUEST: //21
            u = usersManager->Login(document["email"].GetString(), document["password"].GetString());
            if (u != nullptr) {
                sender.myUser = u;
            }
            c = new CommandLogin(u);
            sender.sendMessage(c->getSerializedString());
            //delete u;
            delete c;
            break;

        default:
            break;
    }

    if (sender.myUser == nullptr) {
        //Not Logged yet. The following switch case is reserved to logged users.
        return;
    }

    switch (id) {
        case COMMAND_MEDIA_REQUEST:
            if (!document.HasMember("media-id")) {
                cout << "Invalid message without media-id received: " << message << "\n";
                return;
            }

            c = new CommandMedia(document["media-id"].GetString(),
                                 MediaManager::getMediaById(document["media-id"].GetString()));
            sender.sendMessage(c->getSerializedString());
            delete c;
            break;


        case COMMAND_ADD_CONTACT_REQUEST:
            //document["email"] = email of the other contact. Search it in the db, fetch the id and so create a new chat between them.
            u = usersManager->getUserByEmail(document["email"].GetString());

            if (u == nullptr) {
                c = new CommandGeneric(COMMAND_ADD_CONTACT_RESPONSE, false, "User not found");
                sender.sendMessage(c->getSerializedString());
                delete c;
                break;
            }

            ch = new Chat("");
            ch->addPartecipant(u->id);
            ch->addPartecipant(sender.myUser->id);

            result = chatManager->createChat(ch);

            c = new CommandGeneric(COMMAND_ADD_CONTACT_RESPONSE, result == "ok", result);
            sender.sendMessage(c->getSerializedString());
            delete c;
            break;

        case COMMAND_DELETE_CHAT_REQUEST:
            /*
             * Packet composition:
             *     document["chat-id"]
             *     document["isGroup"]
             */
            result = chatManager->deleteChat(document["chat-id"].GetString(), sender.myUser->id);

            c = new CommandGeneric(COMMAND_DELETE_CHAT_RESPONSE, result == "ok", result);
            sender.sendMessage(c->getSerializedString());
            delete c;
            break;

        case COMMAND_CREATE_GROUP_REQUEST:
            /*
             * Packet composition:
             *      document["ids"] => array of int
             */
            ch = new Chat("");
            if (document["ids"].IsArray()) {
                // const Value& ids = document["ids"];

                for (SizeType i = 0; i < document["ids"].Size(); i++) {
                    ch->addPartecipant(document["ids"][i].GetString());
                }
                result = chatManager->createChat(ch);

                c = new CommandGeneric(COMMAND_CREATE_GROUP_RESPONSE, result == "ok", result);
                sender.sendMessage(c->getSerializedString());
                delete c;
            }

            break;

        case COMMAND_MESSAGE_REQUEST:
            /*
             * Packet composition:
             *      "chat-id": id of selected chat
             *      "text":  string containing the message content
             *      "media": null or base64 string
             */
            m = new Message(document["content"].GetString(), sender.myUser->id,
                            sender.myUser->name + sender.myUser->surname, document["media"].GetString());
            ch = chatManager->addMessageToChat(document["chat-id"].GetString(), m);

            if (ch == nullptr) {
                cout << "Received an invalid message.\n";
                delete m;
                break;
            }

            c = new CommandMessage(ch->Id, m);

            for (auto p: ch->Participants) {
                c1 = server->getClientByUserId(p);
                if (c1 != nullptr) {
                    c1->sendMessage(c->getSerializedString());
                }
            }

            delete c;
            delete m;

            break;

        case COMMAND_FETCH_CONTACTS_REQUEST:

            chats = chatManager->fetchChats(sender.myUser->id);

            for (auto p : chats) {
                if (!p->IsGroup) {
                    p->Participants.remove(sender.myUser->id);
                    u = usersManager->getUserById(p->Participants.front());
                    p->Name = u->name + " " + u->surname;
                    delete u;
                }
            }

            c = new CommandFetchContacts(chats);
            sender.sendMessage(c->getSerializedString());
            delete c;
            for (auto p : chats) {
                delete p;
            }
            chats.clear();

            break;

        case COMMAND_FETCH_CHAT_REQUEST:

            ch = chatManager->getChatById(document["chat-id"].GetString());
            result = "";
            if (!ch->IsGroup) {
                ch->Participants.remove(sender.myUser->id);
                result = getUserStatus(ch->Participants.front());
            }
            c = new CommandFetchChat(ch->messagges, result);
            sender.sendMessage(c->getSerializedString());
            delete c;
            delete ch;

        default:
            break;
    }

}

void Dispatcher::executeResponse(Client &sender, Command *c) {

    switch (c->id) {
        case COMMAND_TEST:
            //Casting Command al vero tipo.
            dynamic_cast<CommandTest *>(c)->print();
            break;

        case COMMAND_REGISTER_RESPONSE:
            break;

        case COMMAND_LOGIN_RESPONSE:
            break;

        default:
            break;
    }

}

void Dispatcher::logoutUser(const string &id) {
    usersManager->updateUserLastAccess(id);
}

string Dispatcher::getUserStatus(const string &user_id) {
    if (server->getClientByUserId(user_id) != nullptr) {
        return "online";
    } else {
        long long count = usersManager->getLastAccess(user_id);
        if (count == 0) {
            cout << "User " << user_id << " doesn't have a last-access time!\n";
            return "Undefined";
        } else {
            return utils::formatDateFromMilliseconds(count);
        }
    }
}


