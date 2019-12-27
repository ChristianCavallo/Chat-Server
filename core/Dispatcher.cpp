//
// Created by chryc on 14/12/2019.
//
#include <rapidjson/prettywriter.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/document.h>
#include "../Commands/Command.h"
#include "Dispatcher.h"


void Dispatcher::executeRequest(Client &sender, string message) {
    Document document; //definisci un document
    document.Parse(message.c_str()); //gli passi la stringa json e poi puoi accedere ai compi in questo modo:
    // string email = document["email"]

    //il dispatche legge la stringa e la fa ridiventare un json e analizza il campo ID come prima cosa, ok?ok
    if (!document.HasMember("id")) {
        cout << "Invalid message received: " << message << "\n";
        return;
    }

    int id = document["id"].GetInt();

    switch (id) {
        Command *c;
        User* u; //o lo fai qua
        case COMMAND_TEST:
            c = new CommandTest(document["message"].GetString());
            sender.sendMessage(c->getSerializedString());
            delete c;
            break;

        case COMMAND_REGISTER_REQUEST:
            //qua verra gestita la richiesta di registrazione...
            //dovrebbe funzionare tipo cosi
            //int risultato = gestoreUtenti.register(document["name"], document["surname"], document["email"], document["password"]);
            //lui fa la registrazione... tipo bho ti fai ritornare un numero che ti fa capire se ha avuto successo

            //anzi, mando il risulato al client... e lui capisce da solo se è andato bene o no xD
            //c = new CommandRegister(risultato);
            sender.sendMessage(c->getSerializedString());
            delete c;

            break;

        case COMMAND_LOGIN_REQUEST: //21
        /*
         * Il dispatcher è un distributore di operazioni. In questo caso ci troviamo difronte ad una richiesta di login.
         * Chi gestisce le richieste di login? Lo users_manager. Quindi il dispatchere deve passare l'operazione a lui
         * Capito?si
         */
            //ultimo problema... qua nn puoi definire variabili... cioè dentro lo switch
            u = usersManager->Login(document["email"].GetString(), document["password"].GetString());

            c = new CommandLogin(u);
            sender.sendMessage(c->getSerializedString());
            delete u;
            delete c;
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
