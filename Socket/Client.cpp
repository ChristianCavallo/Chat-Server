//
// Created by chryc on 06/12/2019.
//



#include "Client.h"
#include <iostream>
#include <thread>
#include "../include/rapidjson/prettywriter.h"
#include "../include/rapidjson/stringbuffer.h"
#include "../include/rapidjson/document.h"
#include "../Commands/Command.h"

using namespace std;
using namespace rapidjson;

Client::Client(SOCKET &sck) {
    this->sck = sck;
    this->crypto = new Crypto();
}

void Client::start() {
    this->t = thread(&Client::receive, this);
}

void Client::receive() {
    int received = 0;
    int a = 0;
    char syncBuffer[4];
    char* buffer;

    cout << "Starting receive!\n";
    do{

        received = recv(this->sck, syncBuffer, 4, 0);

        if(received <= 0){
            break;
        }

        if(received != 4){
            continue;
        }

        memcpy(&a, syncBuffer, 4);
        if(a != 12344321){
            cout << "Sync error on step 1. Received: " << a << "\n";
            continue;
        }

        received = recv(this->sck, syncBuffer, 4, 0);

        if(received != 4){
            continue;
        }

        memcpy(&a, syncBuffer, 4);
        if(a < 0 || a > 1048000){ //Payload < 1Mb
            cout << "Size error: " << a << "\n";
            continue;
        }
        cout << "Payload size is " << a << "\n";

        //allocate a new buffer with sizeof(a)
        //TODO: REMEMBER TO DELETE THE BUFFER!!!!!
        buffer = new char[a + 1];
        received = recv(this->sck, buffer, a, MSG_WAITALL);
        if(received != a){
            cout << "Error while receiving! Received: " << received << "  Expected: " << a << "\n";
            continue;
        }
        buffer[a] = '\0';

        received = recv(this->sck, syncBuffer, 4, 0);

        if (received != 4) {
            continue;
        }

        memcpy(&a, syncBuffer, 4);
        if (a != 43214321) {
            cout << "Sync error on step 1.\n";
            continue;
        }


        if (!crypted) {
            Document document;
            document.Parse(buffer);
            if (document.HasMember("id") && document.HasMember("key")) {
                int id = document["id"].GetInt();
                string key = document["key"].GetString();
                if (id == 0) {
                    crypto->setClientPublicKey(const_cast<char *>(key.c_str()));
                    string str(crypto->pub_key);
                    CommandKey *cmdKey = new CommandKey(0, str);
                    sendMessage(cmdKey->getSerializedString());
                    delete cmdKey;
                    crypted = true;
                    cout << "Connection is now secure!\n";
                }
            }

        } else {
            char *decrypted = crypto->decrypt(buffer);
            cout << "Received a new message: " << decrypted << "\n";
            string s(decrypted);
            sendMessage(s);
        }
        /*if(strcmp(buffer, "ciao") == 0){

            StringBuffer sb;
            PrettyWriter<StringBuffer> writer(sb);

            Command* c = new Command(12345, "Pollo", "sono un pollo");
            c->Serialize(writer);

            string message = sb.GetString();
            sendMessage(message);
            delete c;
        }*/

    } while(received > 0);

    cout << "Client exited from receiving cause received data was 0 or less. Closing the socket...\n";

    this->close();
}


void Client::close() {
    // shutdown the connection since we're done
    if (shutdown(this->sck, SD_SEND) == SOCKET_ERROR) {
        cout << "Shutdown failed with error: " << WSAGetLastError() << "\n";
    }

    // cleanup
    closesocket(this->sck);

    //Delete the crypto
    delete crypto;

    //Deattacching the thread
    this->t.detach();
    this->closed = true;
    cout << "Client closed and thread deattached!\n";

}


void Client::sendMessage(string msg) {

    char *content;
    int messageLen = 0;
    if (crypted) {
        content = crypto->encrypt(const_cast<char *>(msg.c_str()));
        messageLen = crypto->lastCryptedLen;
    } else {
        content = const_cast<char *>(msg.c_str());
        messageLen = msg.size();
    }

    char *buffer = new char[messageLen + 12];
    int num = 12344321;
    memcpy(buffer, &num, 4);

    memcpy(buffer + 4, &messageLen, 4);

    memcpy(buffer + 8, content, messageLen);
    num = 43214321;
    memcpy(buffer + 8 + messageLen, &num, 4);

    int result = send(this->sck, buffer, messageLen + 12, 0);
    if (result == SOCKET_ERROR) {
        cout << "Data send failed with error: " << WSAGetLastError() << "\n";
        this->close();
    } else {
        //cout << "Message sent: " << msg << "\n";
    }

    delete[] buffer;
    if (crypted) {
        delete[] content;
    }
}

Client::~Client() {

}



