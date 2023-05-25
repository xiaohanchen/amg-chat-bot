//
// Created by Haiying on 16/05/2023.
//

#include <arpa/inet.h>
#include <unistd.h>
#include "../include/chat_server.h"
#include "../include/server_worker.h"


ChatServer::ChatServer() {
}

ChatServer::ChatServer(int maxWorkerThreadNum) : _maxWorkerThreadNum(maxWorkerThreadNum) {}

ChatServer::~ChatServer() {

}

bool ChatServer:: start(int port, int connectionQueueLen, int maxNumWorker) {
    try {

        //open socket
        _initSocket();

        //bind port to socket
        _bindAddress(port);

        //start listen, async (always listening to new connections until connectionQueueLen is reached)
        _listenToClientConnections(connectionQueueLen);
        
        //start server workers as thread to check and read socket buffer
        for (int i = 0; i < maxNumWorker; ++i) {
            ServerWorker * worker = new ServerWorker();
            _serverWorkers.push_back(worker);
            worker->startRun();
        }

        //start thread accepting clients
        new std::thread(&ChatServer::acceptClient, this);
        
        

        
    } catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
        throw std::runtime_error("Failed to start the Chat Server");
    }
    return true;
}



void ChatServer::acceptClient(){
    //should use some other condition
    while(true){
        //accept clients, this is blocking
        int connectedClientSocket = _acceptClient(0);
        std::cout << "socket contected with ip=" << inet_ntoa(_clientAddr.sin_addr)
            << "port=" << ntohs(_clientAddr.sin_port)
            << "fd=" << connectedClientSocket << std::endl;
        //register the connected client and new thread to recv message
        ConnectedClient *pClient = new ConnectedClient(connectedClientSocket);


        //BIO mode, new thread for each new connection
        //pClient->startRecv();

        //NIO mode, add connection if the worker is not full.
        // better solution could be: distribute clients across workers
        for (const auto &item: _serverWorkers){
            if (item->isAvailable()){
                item->addConnectedClient(*pClient);
                break;
            }
        }

    }
}

void ChatServer::close(){
    //close the socket
    ::close(_sockFd);
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


void ChatServer::_listenToClientConnections(int connectionQueueLen) {
    std::cout << "start listen to clients" << std::endl;
    //listen to clients connect request
    if (listen(_sockFd, connectionQueueLen) < 0) {
        throw std::runtime_error(strerror(errno));
    }
}

int ChatServer::_acceptClient(int timeout) {
    std::cout << "wait for client to be connected" << std::endl;

    //accept client connection
    socklen_t socketSize  = sizeof(_clientAddr);
    int clientFd = accept(_sockFd, (struct sockaddr*)&_clientAddr, &socketSize);
    if (clientFd < 0) {
        throw std::runtime_error(strerror(errno));
    }

    //todo manage connected client
    return clientFd;
}



