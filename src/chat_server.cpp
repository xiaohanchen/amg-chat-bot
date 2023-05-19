//
// Created by Haiying on 16/05/2023.
//

#include "../include/chat_server.h"


ChatServer::ChatServer() {
}

ChatServer::~ChatServer() {
}

bool ChatServer::start(int port, int max_connections, int max_events) {
    try {
        _initSocket();
        _bindAddress(port);
        _listenToClientConnections(max_connections);
        _maxEventAllowed = max_events;
    } catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
        throw std::runtime_error("Failed to start the Chat Server");
        return false;
    }
    return true;
}



/* ================================== BELOW ARE THE PRIVATE METHODS==================================*/
void ChatServer::_initSocket() {
    //start TCP STREAM socket
    _sockFd = socket(AF_INET, SOCK_STREAM, 0);
    std::cout << "socket created with fd=" << _sockFd << std::endl;

    if (_sockFd < 0) {
        throw std::runtime_error("failed to create socket");
    }
}

void ChatServer::_bindAddress(int port) {
    //bind the socket to the address
    _serverAddr.sin_family = AF_INET;
    _serverAddr.sin_addr.s_addr = INADDR_ANY;
    _serverAddr.sin_port = htons(port);

    //bind the socket to the address
    if (bind(_sockFd, (struct sockaddr*) &_serverAddr, sizeof(_serverAddr)) < 0) {
        throw std::runtime_error(strerror(errno));
    }


}


void ChatServer::_listenToClientConnections(int maxNumOfClients) {
    //listen to clients connect request
    if (listen(_sockFd, maxNumOfClients) < 0) {
        throw std::runtime_error(strerror(errno));
    }
}

int ChatServer::acceptClient(int timeout) {
    //accept client connection
    int clientFd = accept(_sockFd, NULL, NULL);
    if (clientFd < 0) {
        throw std::runtime_error(strerror(errno));
    }

    //todo manage connected client
    return clientFd;
}


