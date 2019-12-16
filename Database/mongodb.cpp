//
// Created by chryc on 11/12/2019.
//

#include "mongodb.h"
#include "../Commands/Command.h"
#include "../Oggetti/GestoreUtenti.h"
#include "../Oggetti/Utenti.h"


//funzione di creazione di un documento(riga nel modella relazionale)
void Mongodb::CreateCollection(string name) {

     Utenti *utente = new Utenti();
     coll = db[name];
     cout << "ciao\n";

     auto builder = bsoncxx::builder::stream::document{};
     cout << "Fine creazone del document\n";
     printf("\n");
        bsoncxx::document::value doc_value = builder

                << "name" << utente->Name
                << "surname" << utente->Surname
                << "email" << utente->Email
                << "password" << utente->Password
                << bsoncxx::builder::stream::finalize;
        cout << "Fine inserimento elementi\n";
        bsoncxx::document::view view = doc_value.view();
        cout << "Abilita\n";
        //bsoncxx::stdx::optional<mongocxx::result::insert_one>
        coll.insert_one(doc_value.view());
        cout <<"inserito nella collection\n";
}


Mongodb::~Mongodb() {
    delete inst;
    delete client;

}
