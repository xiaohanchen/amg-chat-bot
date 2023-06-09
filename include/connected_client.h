//
// Created by Haiying on 18/05/2023.
//
#include <thread>
#include <iostream>

#ifndef AMG_CHAT_BOT_CONNECTED_SOCKET_H
#define AMG_CHAT_BOT_CONNECTED_SOCKET_H

#endif //AMG_CHAT_BOT_CONNECTED_SOCKET_H

class ConnectedClient{

private:
    //file descriptor when client connection accepted
    int _connectedSockFd;

    //thread to
    std::thread * _msgConsumerThread = nullptr;

    /**
     * start a new thread to continuously receive data from client:
     * 1, check if there is data in the buffer (blocking)
     * 2, if there is data, receive it
     */
    void _receiveData();

public:

    explicit ConnectedClient(int connectedSockFd);

    /**
     * deprecated, this is a BIO implementation
     */
    void startRecv();

    /**
     * get connected socket file descriptor
     * @return
     */
    int getConnectedSockFd() const;

    /**
     * read from buffer, should check buffer beforehand
     * called by ServerWorker
     *
     * @param buffer buffer to be written to
     * @return
     */
    char * recvFromBuffer();

};
