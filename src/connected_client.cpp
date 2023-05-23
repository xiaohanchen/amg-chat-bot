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

        std::cout << "read buffer checking..." << std::endl;
        int bufferCheckRes = select(_connectedSockFd + 1, &_readfds, NULL, NULL, NULL);

        if(bufferCheckRes == -1){
            std::cout << "read buffer check failed" << std::endl;
        }else if(bufferCheckRes == 0){
            std::cout << "read buffer check timeout" << std::endl;
        }else{
            char _buffer[MAX_CHAR_TO_READ] = {0};
            ssize_t bytesReceived = recv(_connectedSockFd, _buffer, MAX_CHAR_TO_READ, 0);
            if(bytesReceived < 1){
                std::cout << "error to recv" << _buffer << std::endl;
            }else{
                std::cout << "received bytes: " << bytesReceived << std::endl;
                std::cout << "received message: " << _buffer << std::endl;

                //ACK to client
                std::string msgAck = "ACK";
                ssize_t sendRes = send(_connectedSockFd, &msgAck, msgAck.length(), 0);
                if(sendRes < 0) {
                    std::cout << "error to send ACK" << std::endl;
                }
            }
        }

    }

}



