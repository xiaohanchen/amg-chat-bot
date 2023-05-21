//
// Created by xiaohan on 21/05/2023.
//

#include <sys/select.h>
#include <sys/socket.h>
#include "../include/connected_client.h"
#include "../include/constants.h"

ConnectedClient::ConnectedClient(int connectedSockFd)
    : _connectedSockFd(connectedSockFd) {

}


void ConnectedClient::startRecv(){

    _msgConsumerThread = new std::thread(&ConnectedClient::_receiveData, this);

    return;

}





void ConnectedClient::_receiveData(){
    while(true) {

        fd_set _readfds;
        FD_ZERO(&_readfds);
        FD_SET(_connectedSockFd, &_readfds);
        int res = select(_connectedSockFd + 1, &_readfds, NULL, NULL, NULL);

        if(res > 0){
            char _buffer[MAX_CHAR_TO_READ];
            ssize_t bytesReceived = recv(_connectedSockFd, _buffer, sizeof(_buffer), 0);
            std::cout << "bytesReceived=" << _buffer << std::endl;
        }

    }

}



