//
// Created by chryc on 14/12/2019.
//

#include "Dispatcher.h"
#include "../Socket/Client.h"

using namespace SocketCommands;

void Dispatcher::executeRequest(Client &sender, const string &message) {
    Document document;

    document.Parse(message.c_str());

    if (!document.HasMember("id")) {
        cout << "Invalid message received: " << message << "\n";
        return;
    }

    int id = document["id"].GetInt();

    switch (id) {
        case COMMAND_TEST: {
            Command *c = new CommandTest(document["message"].GetString());
            sender.sendMessage(c->getSerializedString());
            delete c;
            break;
        }

        case COMMAND_REGISTER_REQUEST: {

            User *u = new User("", document["name"].GetString(), document["surname"].GetString(),
                         document["email"].GetString(), document["password"].GetString());
            Command *c = new CommandRegistration(usersManager->Registration(u));
            sender.sendMessage(c->getSerializedString());
            delete u;
            delete c;
            break;
        }

        case COMMAND_LOGIN_REQUEST: {
            User *u = usersManager->Login(document["email"].GetString(), document["password"].GetString());
            if (u != nullptr) {
                sender.myUser = u;
            }
            Command *c = new CommandLogin(u);
            sender.sendMessage(c->getSerializedString());

            //delete u;
            delete c;
            break;
        }

        default:
            break;
    }

    if (sender.myUser == nullptr) {
        //Not Logged yet. The following switch case is reserved to logged users.
        cout << "An unauthenticated user is trying to get some info!!\n";
        return;
    }

    switch (id) {
        case COMMAND_MEDIA_REQUEST: {
            if (!document.HasMember("media-id")) {
                cout << "Invalid message without media-id received: " << message << "\n";
                return;
            }

            Command *c = new CommandMedia(document["media-id"].GetString(),
                                          MediaManager::getMediaById(document["media-id"].GetString()));
            sender.sendMessage(c->getSerializedString());
            delete c;
            break;
        }

        case COMMAND_ADD_CONTACT_REQUEST: {
            //document["email"] = email of the other contact. Search it in the db, fetch the id and so create a new chat between them.
            User *u = usersManager->getUserByEmail(document["email"].GetString());

            if (u == nullptr) {
                Command *c = new CommandGeneric(COMMAND_ADD_CONTACT_RESPONSE, false, "User not found");
                sender.sendMessage(c->getSerializedString());
                delete c;
                break;
            }

            Chat *ch = new Chat("");
            ch->addPartecipant(u->id);
            ch->addPartecipant(sender.myUser->id);

            string result = chatManager->createChat(ch);

            Command *c = new CommandGeneric(COMMAND_ADD_CONTACT_RESPONSE, result == "ok", result);
            sender.sendMessage(c->getSerializedString());
            delete c;
            break;
        }

        case COMMAND_DELETE_CHAT_REQUEST: {
            /*
             * Packet composition:
             *     document["chat-id"]
             *     document["isGroup"]
             */
            string result = chatManager->deleteChat(document["chat-id"].GetString(), sender.myUser->id);

            Command *c = new CommandGeneric(COMMAND_DELETE_CHAT_RESPONSE, result == "ok", result);
            sender.sendMessage(c->getSerializedString());
            delete c;

            if(result == "ok"){
                auto *m = new Message(
                        "User '" + sender.myUser->name + " " + sender.myUser->surname + "' has left the group",
                        "1234567890",
                        "Server", "");
                Chat *ch = chatManager->addMessageToChat(document["chat-id"].GetString(), m);

                if (ch == nullptr) {
                    delete m;
                    break;
                }

                Command *c = new CommandMessage(ch->Id, m);

                for (const auto &p: ch->Participants) {
                    Client *c1 = server->getClientByUserId(p);
                    if (c1 != nullptr) {
                        c1->sendMessage(c->getSerializedString());
                    }
                }

                delete c;
                delete m;
                delete ch;
            }

            break;
        }
        case COMMAND_CREATE_GROUP_REQUEST: {
            /*
             * Packet composition:
             *      document["ids"] => array of int
             *      document["name"] => Name of the group
             */
            Chat *ch = new Chat("");
            if (document["ids"].IsArray()) {
                // const Value& ids = document["ids"];

                for (SizeType i = 0; i < document["ids"].Size(); i++) {
                    ch->addPartecipant(document["ids"][i].GetString());
                }
                ch->addPartecipant(sender.myUser->id);
                ch->Name = document["name"].GetString();
                string result = chatManager->createChat(ch);

                Command *c = new CommandGeneric(COMMAND_CREATE_GROUP_RESPONSE, result == "ok", result);
                sender.sendMessage(c->getSerializedString());
                delete c;
            }

            break;
        }
        case COMMAND_MESSAGE_REQUEST: {
            /*
             * Packet composition:
             *      "chat-id": id of selected chat
             *      "text":  string containing the message content
             *      "media": null or base64 string
             */
            auto *m = new Message(document["content"].GetString(), sender.myUser->id,
                                  sender.myUser->name + " " + sender.myUser->surname, document["media"].GetString());
            Chat *ch = chatManager->addMessageToChat(document["chat-id"].GetString(), m);

            if (ch == nullptr) {
                cout << "Received an invalid message.\n";
                delete m;
                break;
            }

            Command *c = new CommandMessage(ch->Id, m);

            for (const auto &p: ch->Participants) {
                Client *c1 = server->getClientByUserId(p);
                if (c1 != nullptr) {
                    c1->sendMessage(c->getSerializedString());
                }
            }

            delete c;
            delete m;
            delete ch;
            break;
        }
        case COMMAND_FETCH_CONTACTS_REQUEST: {

            vector<Chat *> chats = chatManager->fetchChats(sender.myUser->id);

            for (auto p : chats) {
                p->Participants.remove(sender.myUser->id);
                if (!p->IsGroup) {
                    User *u = usersManager->getUserById(p->Participants.front());
                    p->Name = u->name + " " + u->surname;
                    delete u;
                }

                if (p->messagges.size() > 20) {
                    for (int i = 0; i < p->messagges.size() - 20; i++) {
                        delete p->messagges.at(i);
                    }
                    p->messagges.erase(p->messagges.begin(), p->messagges.end() - 20);
                }

                p->NumNotifications = getNotifiesCount(p->messagges, sender.myUser->lastaccess);

            }

            sort(chats.begin(), chats.end(), [](const Chat* lhs, const Chat* rhs) {
                return lhs->NumNotifications > rhs->NumNotifications;
            });

            Command *c = new CommandFetchContacts(chats);
            sender.sendMessage(c->getSerializedString());
            delete c;
            for (auto p : chats) {
                delete p;
            }
            chats.clear();

            sender.myUser->lastaccess = bsoncxx::types::b_date{std::chrono::system_clock::now()};
            break;
        }
        case COMMAND_FETCH_CHAT_REQUEST: {

            Chat *ch = chatManager->getChatById(document["chat-id"].GetString());
            string result = "";

            if (ch == nullptr) {
                Command *c = new CommandGeneric(COMMAND_ERROR, false, "Chat not available. The user removed it.");
                sender.sendMessage(c->getSerializedString());
                delete c;
                break;
            }

            if (!ch->IsGroup) {
                ch->Participants.remove(sender.myUser->id);
                result = getUserStatus(ch->Participants.front());
            }

            if (ch->messagges.size() > 20) {
                for (int i = 0; i < ch->messagges.size() - 20; i++) {
                    delete ch->messagges.at(i);
                }
                ch->messagges.erase(ch->messagges.begin(), ch->messagges.end() - 20);
            }

            Command *c = new CommandFetchChat(ch->messagges, result);
            sender.sendMessage(c->getSerializedString());
            delete c;
            delete ch;
            sender.myUser->lastaccess = bsoncxx::types::b_date{std::chrono::system_clock::now()};
            break;
        }
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
    }

    long long count = usersManager->getLastAccess(user_id).value.count();

    return "Last access " + utils::formatDateFromMilliseconds(count);

}

int Dispatcher::getNotifiesCount(vector<Message *> mv, bsoncxx::types::b_date lastaccess) {
    int notifies = 0;
    if(mv.empty()){
        return 0;
    }
    //Check if the date of last message is > than last access
    if (mv.at(mv.size() - 1)->ReceptionDate > lastaccess) {
        //Calculate the number of notifies
        for (int i = 0; i < mv.size(); i++) {
            if (mv.at(i)->ReceptionDate > lastaccess) {
                notifies = mv.size() - i;
                break;
            }
        }
    }

    return notifies;
}