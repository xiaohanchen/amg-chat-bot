//
// Created by Haiying on 16/05/2023.
//


#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include "server_worker.h"

#ifndef AMG_CHAT_BOT_CHAT_SERVER_H
#define AMG_CHAT_BOT_CHAT_SERVER_H

/**
 * this sever has functions :-
 * 1, init socket and accept connections
 * 2, manage a vector of clients
 * 3, listen to client event
 * 4, admin operations on server itself
 */
class ChatServer {

private:
    //file descriptor for the socket
    int _sockFd;

    //server address
    struct sockaddr_in _serverAddr;

    //client address
    struct sockaddr_in _clientAddr;

    //max worker thread num (only for NIO)
    int _maxWorkerThreadNum = 1;

    std::vector<ServerWorker *> _serverWorkers;


    /**
     * initialise the socket
     */
    void _initSocket();

    /**
     * bind the address to the socket
     */
    void _bindAddress(int port);

    /**
     * listen to clients, blocking style
     * @param connectionQueueLen
     */
    void _listenToClientConnections(int connectionQueueLen);

    /**
     * accept a connection from client
     * @param timeout timeout in seconds, 0 means blocking
     * @return
     */
    int _acceptClient(int timeout=0);
public:
    explicit ChatServer(int maxWorkerThreadNum);
    ChatServer();
    ~ChatServer();

    /**
     * initialise the server, creating socket, start listening on port
     * @param port
     * @param connectionQueueLen
     * @param max_events
     * @return
     */
    bool start(int port, int connectionQueueLen=3, int maxNumWorker = 1);

    /**
     * accept client connection
     */
    void acceptClient();

    /**
     * shut down the server socket
     */
    void close();

};


#endif //AMG_CHAT_BOT_CHAT_SERVER_H
