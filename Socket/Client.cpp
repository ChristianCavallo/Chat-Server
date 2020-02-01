//
// Created by chryc on 06/12/2019.
//



#include "Client.h"
#include "../core/Dispatcher.h"

using namespace std;
using namespace rapidjson;

Client::Client(SOCKET &sck) {
    this->sck = sck;
    this->crypto = new Crypto();
    this->id = 0;
    this->myUser = nullptr;
}

void Client::start() {
    this->t = thread(&Client::receive, this);
}

void Client::receive() {

        int received = 0;
        int a = 0;
        char syncBuffer[4];
        char *buffer = nullptr;

        cout << "Starting receive!\n";
        do {
            try {


                received = recv(this->sck, syncBuffer, 4, 0);

                if (received <= 0) {
                    break;
                }

                if (received != 4) {
                    continue;
                }

                memcpy(&a, syncBuffer, 4);
                if(a != 12344321){
                    cout << "Sync error on step 1. Received: " << a << "\n";
                    continue;
                }

                received = recv(this->sck, syncBuffer, 4, 0);

                if (received != 4) {
                    continue;
                } else if (received <= 0) {
                    break;
                }

                memcpy(&a, syncBuffer, 4);
                if (a < 0) {
                    cout << "Size error: " << a << "\n";
                    continue;
                }

                buffer = new char[a + 1];
                received = recv(this->sck, buffer, a, MSG_WAITALL);
                if (received != a) {
                    cout << "Error while receiving! Received: " << received << "  Expected: " << a << "\n";
                    continue;
                } else if (received <= 0) {
                    break;
                }
                buffer[a] = '\0';

                received = recv(this->sck, syncBuffer, 4, 0);

                if (received != 4) {
                    continue;
                } else if (received <= 0) {
                    break;
                }

                memcpy(&a, syncBuffer, 4);
                if (a != 43214321) {
                    cout << "Sync error on step 1.\n";
                    continue;
                }


                if (!cryptedRSA) {
                    Document document;
                    document.Parse(buffer);
                    if (document.HasMember("id") && document.HasMember("key")) {
                        int id = document["id"].GetInt();
                        string key = document["key"].GetString();
                        if (id == 0) {
                            crypto->setClientPublicKey(const_cast<char *>(key.c_str()));
                            cryptedRSA = true;

                            string str(crypto->pub_key);
                            string aes_key = base64_encode(crypto->AES_Key, 32);
                            string aes_iv = base64_encode(crypto->AES_iv, crypto->AES_BLOCK_SIZE);
                            auto *cmdKey = new SocketCommands::CommandKey(str, aes_key, aes_iv);
                            sendMessage(cmdKey->getSerializedString());

                            delete cmdKey;

                            cryptedAES = true;
                            cout << "Connection is now secure!\n";
                        }
                    }

                } else {
                    string decrypted = crypto->decrypt_AES(buffer);
                    cout << "Received a new message: " << decrypted << "\n";
                    Dispatcher::getInstance().executeRequest(*this, decrypted);

                    decrypted.clear();
                }

                delete[] buffer;

            } catch (exception ex) {
                cout << "Exception caught: " << ex.what() << "\n";
            }
            
        } while (received > 0);

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

    if (myUser != nullptr) {
        Dispatcher::getInstance().logoutUser(myUser->id);
        cout << "Logout user: " << myUser->id << "\n";
        delete myUser;
    }

}


void Client::sendMessage(const string &msg) {

    char *content;
    int messageLen = 0;
    if (cryptedRSA && !cryptedAES) {
        content = crypto->encrypt_RSA(const_cast<char *>(msg.c_str()));
        messageLen = crypto->lastCryptedLen;
    } else if (cryptedAES) {

        content = crypto->encrypt_AES(const_cast<char *>(msg.c_str()));
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
        cout << "Response sent\n";
    }

    delete[] buffer;
    if (cryptedRSA) {
        delete[] content;
    }
}

Client::~Client()=default;



