//
// Created by chryc on 11/12/2019.
//

#include "mongodb.h"
#include "../Commands/Command.h"
#include "../Managers/User.h"

//Funzione Aggiungi utente e verifica se l'utente esiste già
string Mongodb::addUser(User *u) {     //Passo l'utente ovverò tutti i campi creati

    User *u2 = getUser(u->email);
    if (u2 != nullptr) {
        cout << "Utente gia esistente..\n";
        delete u2; //xke dentro l'if, u2 è un vero utente.. e va cancellato xke l'ho allocato con il new
        return "User already exist.";
    }


    this->coll = db["users"];
    auto builder = bsoncxx::builder::stream::document{};
    bsoncxx::document::value doc_value = builder

            << "name" << u->name
            << "surname" << u->surname
            << "email" << u->email
            << "password" << u->password
            << bsoncxx::builder::stream::finalize;
    bsoncxx::document::view view = doc_value.view();
    coll.insert_one(view);
    cout << "Utente inserito \n";
    //Deve tornare True;
    return "ok";
}

Mongodb::~Mongodb() {
    delete inst;
    delete client;

}

//ritorna un user in base all email
User *Mongodb::getUser(const string &email) {

    coll = this->db["users"];                                           // SELECT * FROM users WHERE email = 'email'
    bsoncxx::stdx::optional<bsoncxx::document::value> result = coll.find_one(
            document{} << "email" << email << finalize);


    if (result) {
        //std::cout << bsoncxx::to_json(*result) << "\n";
        string email = result->view()["email"].get_utf8().value.to_string();
        string name = result->view()["name"].get_utf8().value.to_string();
        string surname = result->view()["surname"].get_utf8().value.to_string();
        string password = result->view()["password"].get_utf8().value.to_string();

        string id = result->view()["_id"].get_oid().value.to_string();
        //in teoria, è finita. ma no che non partiva per il trattino basso xD pignoli xD già xD cmq grazie xD un atitmo che faccio pipì e torno xD
        User *u = new User(id, name, surname, email, password);
        return u;

    }

    return nullptr;
}


//Allora, esistono 2 tipi di funzioni. Quelle che eseguono senza ritornare nessuno stato, lo so... chry void nt posso mettere int o che ritorna un oggetto... lo so

