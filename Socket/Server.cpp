//
// Created by chryc on 06/12/2019.
//

#include "Server.h"




using namespace std;

int index = 0;

Server::Server() {
    this->stopFlag = false;

}

void Server::start() {
    this->t = thread(&Server::startListen, this);
}

void Server::startListen() {
    WSADATA wsaData;
    int iResult;
    SOCKET ListenSocket = INVALID_SOCKET;

    struct addrinfo *result = NULL;
    struct addrinfo hints;

    iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed with error: %d\n", iResult);
        return;
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    // Resolve the server address and port
    iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
    if ( iResult != 0 ) {
        printf("getaddrinfo failed with error: %d\n", iResult);
        WSACleanup();
        return;
    }

    // Create a SOCKET for connecting to server
    ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (ListenSocket == INVALID_SOCKET) {
        printf("socket failed with error: %ld\n", WSAGetLastError());
        freeaddrinfo(result);
        WSACleanup();
        return;
    }

    // Setup the TCP listening socket
    iResult = bind( ListenSocket, result->ai_addr, (int)result->ai_addrlen);
    if (iResult == SOCKET_ERROR) {
        printf("bind failed with error: %d\n", WSAGetLastError());
        freeaddrinfo(result);
        closesocket(ListenSocket);
        WSACleanup();
        return;
    }

    freeaddrinfo(result);

    iResult = listen(ListenSocket, SOMAXCONN);
    if (iResult == SOCKET_ERROR) {
        printf("listen failed with error: %d\n", WSAGetLastError());
        closesocket(ListenSocket);
        WSACleanup();
        return;
    }

    // Accept a client socket
    cout << "Server initialized on port " << DEFAULT_PORT << "\n";
    this->stopFlag = false;
    while(!stopFlag) {
       // cout << "Start listening for a new client...\n";
        SOCKET clientSocket = accept(ListenSocket, NULL, NULL);
        if (clientSocket == INVALID_SOCKET) {
            printf("accept failed with error: %d\n", WSAGetLastError());
            closesocket(clientSocket);
            continue;
        }

        //Remove closed sessions
        for (int i = 0; i < clients.size(); i++){
            Client* c = clients.at(i);
            if(c->closed){
                clients.erase(clients.begin() + i);
                delete c;
                cout << "Client removed.\n";
                break;
            }
        }

        Client *cl = new Client(clientSocket);
        clients.push_back(cl);
        cl->start();
        cout << "New client connected!\n";
    }

    closesocket(ListenSocket);
    WSACleanup();
    cout << "Server is dead\n";
}


Client *Server::getClientByUserId(string id) {
    if (clients.empty()) {
        return nullptr;
    }
    for (int i = 0; i < clients.size(); i++) {
        Client *c = clients.at(i);
        if (!c->closed && c->myUser != nullptr) {
            if (c->myUser->id == id) {
                return c;
            }
        }

    }

    return nullptr;
}


