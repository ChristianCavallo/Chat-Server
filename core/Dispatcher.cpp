//
// Created by chryc on 14/12/2019.
//
#include <rapidjson/prettywriter.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/document.h>
#include "../Commands/Command.h"
#include "Dispatcher.h"

void Dispatcher::executeRequest(Client &sender, string message) {
    Document document;
    document.Parse(message.c_str());

    Command *c;
    if (!document.HasMember("id")) {
        cout << "Invalid message received: " << message << "\n";
        return;
    }

    int id = document["id"].GetInt();

    switch (id) {
        case COMMAND_TEST:
            c = new CommandTest(document["message"].GetString());
            sender.sendMessage(c->getSerializedString());
            delete c;
            break;

        case COMMAND_REGISTER_REQUEST:
            break;

        case COMMAND_LOGIN_REQUEST: //21
            u = usersManager->Login(document["email"].GetString(), document["password"].GetString());
            c = new CommandLogin(u);
            sender.sendMessage(c->getSerializedString());
            delete u;
            delete c;
            break;

        default:
            break;
    }

    if (sender.user_id.empty()) {
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
            //TODO: Add new contact = Create a new chat between Sender and Receiver
            //My Id = sender.user_id
            //document["email"] = email of the other contact. Search it in the db, fetch the id and so create a new chat between them.

            c = new CommandGeneric(COMMAND_ADD_CONTACT_RESPONSE, true, "contatto gia esistente oppure nnt tt apposto");
            sender.sendMessage(c->getSerializedString());
            delete c;
            break;

        case COMMAND_DELETE_CHAT_REQUEST:

            //TODO: Implement deletion of chats.
            /*
             * Packet composition:
             *     document["chat-id"]
             *     document["isGroup"]
             *
             */
            c = new CommandGeneric(COMMAND_DELETE_CHAT_RESPONSE, true, "chat cancellata o errore");
            sender.sendMessage(c->getSerializedString());
            delete c;
            break;

        case COMMAND_CREATE_GROUP_REQUEST:
            /*
             * Packet composition:
             *      document["ids"] => array of int
             */


            if (document["ids"].IsArray()) {
                // const Value& ids = document["ids"];
                /*
                 *      for (SizeType i = 0; i < ids.Size(); i++)
                 *          int id = ids[i].GetInt()
                 *
                 */

                c = new CommandGeneric(COMMAND_CREATE_GROUP_RESPONSE, true, "chat cancellata o errore");
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
            break;


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
