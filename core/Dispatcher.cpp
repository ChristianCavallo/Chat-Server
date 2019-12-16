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

    if (!document.HasMember("id")) {
        cout << "Invalid message received: " << message << "\n";
        return;
    }

    int id = document["id"].GetInt();

    switch (id) {
        Command *c;
        case COMMAND_TEST:
            c = new CommandTest(document["message"].GetString());
            sender.sendMessage(c->getSerializedString());
            delete c;
            break;

        case COMMAND_REGISTER_REQUEST:
            break;

        case COMMAND_LOGIN_REQUEST:
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
