//
// Created by Haiying on 17/05/2023.
//

#ifndef AMG_CHAT_BOT_CHAT_CLIENT_H
#define AMG_CHAT_BOT_CHAT_CLIENT_H

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include "constants.h"

/**
 * clientServer has functions:-
 * 1, connect to server
 * 2, send command to server in defined frequency
 */
class ChatClient {

private:
    int _sockFd;

    struct sockaddr_in _serverAddr;

    /**
     * initialise the socket
     */
    void _initSocket();

    /**
     * connect to server
     */
    void _connect(int port, const std::string& ip);

    void _setAddress(const std::string& address, int port);

    BufferCheckEnum _checkBuffer(const int fileDescriptor, const int timeout);

    void _receiveData(const int fileDescriptor);

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
     * read message from server
     * @return message
     */
    std::string readMsg();

};


#endif //AMG_CHAT_BOT_CHAT_CLIENT_H
