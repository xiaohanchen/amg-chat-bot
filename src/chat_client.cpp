//
// Created by Haiying on 17/05/2023.
//

#include "../include/chat_client.h"
#include <iostream>
#include <arpa/inet.h>
#include <netdb.h>

ChatClient::ChatClient(){

}


ChatClient::~ChatClient(){

}


bool ChatClient::connectToServer(const std::string& ip, int port){

    //init socket
    _initSocket();

    //convert ip string to sockaddr_in
    _setAddress(ip, port);

    //connect to server
    if (connect(_sockFd , (struct sockaddr *)&_serverAddr , sizeof(_serverAddr)) ){
        throw std::runtime_error("Failed to connect to server");
    }

    std::cout << "connected to server" << std::endl;

    return true;
}


bool ChatClient::sendMsg(const std::string& msg){
    
        //send msg to server using the connected socket
        // 1char=1B
        ssize_t bytesSent = send(_sockFd, msg.c_str(), msg.length(), 0);
        if (bytesSent < 0){
            throw std::runtime_error("Failed to send msg to server");
        }

        if(bytesSent < msg.length()){
            char errorMsg[512];
            sprintf(errorMsg, "msg sent incomplete, %lu bytes out of %lu was sent to client", bytesSent, msg.length());
            throw std::runtime_error(errorMsg);
        }

        std::cout << "msg sent to server" << std::endl;

        return true;
    
}



std::string ChatClient::readMsg(){

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




void ChatClient::_setAddress(const std::string& address, int port) {

    //convert ip address to binary representation required in sockaddr_in
    const int inetSuccess = inet_aton((char*)&address, &_serverAddr.sin_addr);

    if(!inetSuccess) { // inet_addr failed to parse address
        // if hostname is not in IP strings and dots format, try resolve it
        struct hostent *host;
        struct in_addr **addrList;
        //convert hostname to ip address (dns translation)
        if ( (host = gethostbyname( address.c_str() ) ) == nullptr){
            throw std::runtime_error("Failed to resolve hostname");
        }
        addrList = (struct in_addr **) host->h_addr_list;
        _serverAddr.sin_addr = *addrList[0];
    }
    _serverAddr.sin_family = AF_INET;
    _serverAddr.sin_port = htons(port);
}
