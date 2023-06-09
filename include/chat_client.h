//
// Created by Haiying on 17/05/2023.
//

#ifndef AMG_CHAT_BOT_CHAT_CLIENT_H
#define AMG_CHAT_BOT_CHAT_CLIENT_H

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include "constants.h"
#include <thread>

/**
 * clientServer has functions:-
 * 1, connect to server
 * 2, send command to server in defined frequency
 */
class ChatClient {

private:
    //socket opened for the client
    int _sockFd;

    //server addr to send and receive data
    struct sockaddr_in _serverAddr;

    //control the client thread to stop
    bool _connected = false;

    //count
    static int clientCount;

    //client name
    int clientId;

    /**
     * initialise the socket,  client doesnt need to bind
     */
    void _initSocket();

    /**
     * set server address for the socket to connect
     * @param address
     * @param port
     */
    void _setAddress(const std::string& address, int port);

    /**
     * 检查是否有数据可读，如果有，读取数据, BLOCKING
     * @param socketFd
     */
    void _checkBufAndRecv(const int& socketFd);

    /**
     * read message from server
     * @return message
     */
    void _readMsg();


public:
    ChatClient();
    ~ChatClient();


    /**
     * connect to server
     * @param port
     * @param ip
     * @return true if connected
     */
    bool connectToServer(const std::string& ip, int port);

    /**
     * send command to server
     * @param command
     * @return true if success
     */
    bool sendMsg(const std::string& msg);

    /**
     * close the socket
     */
    void close();

    /**
     * get client name
     * @return
     */
    std::string getClientName();

};


#endif //AMG_CHAT_BOT_CHAT_CLIENT_H
