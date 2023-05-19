//
// Created by Haiying on 17/05/2023.
//

#include "../include/chat_client.h"
#include <iostream>

ChatClient::ChatClient(){

}


ChatClient::~ChatClient(){

}


bool ChatClient::connectToServer(int port, const std::string& ip){

    //init socket
    _initSocket();

    //connect to server
    if (connect(_sockFd , (struct sockaddr *)&_serverAddr , sizeof(_serverAddr)) ){
        throw std::runtime_error("Failed to connect to server");
    }

    //read from server thread todo

    return false;
}


void ChatClient::readMsg(){

    // check fd if buffer ready to read


    //read from buffer

}


void ChatClient::_initSocket() {
    //start TCP STREAM socket
    _sockFd = socket(AF_INET, SOCK_STREAM, 0);
    std::cout << "client socket created with fd=" << _sockFd << std::endl;

    if (_sockFd < 0) {
        throw std::runtime_error("failed to create socket");
    }
}

