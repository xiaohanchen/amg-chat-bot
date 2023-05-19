//
// Created by Haiying on 17/05/2023.
//

#ifndef AMG_CHAT_BOT_CHAT_CLIENT_H
#define AMG_CHAT_BOT_CHAT_CLIENT_H

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>

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

public:
    ChatClient();
    ~ChatClient();


    /**
     * connect to server
     * @param port
     * @param ip
     * @return
     */
    bool connectToServer(int port, const std::string& ip);

    /**
     * send command to server
     * @param command
     */
    void sendCommand(const std::string& command);

};


#endif //AMG_CHAT_BOT_CHAT_CLIENT_H
