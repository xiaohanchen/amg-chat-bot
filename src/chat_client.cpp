//
// Created by Haiying on 17/05/2023.
//

#include "../include/chat_client.h"
#include <iostream>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/select.h>
#include <unistd.h>

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

    //listen resp from server
    std::thread *pThread = new std::thread(&ChatClient::_readMsg, this);


    std::cout << "connected to server" << std::endl;
    _connected = true;
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

        std::cout << "msg sent to server" << msg << std::endl;

        return true;
    
}

void ChatClient::close(){
    //close the socket
    ::close(_sockFd);
}


/* ================================== BELOW ARE THE PRIVATE METHODS==================================*/


void ChatClient::_readMsg(){

    while(_connected){
        _checkBufAndRecv(_sockFd);

    }

}

void ChatClient::_checkBufAndRecv(const int& _socketFd ){
    fd_set _readfds;
    FD_ZERO(&_readfds);
    FD_SET(_sockFd, &_readfds);

    // check fd if buffer ready to read
    std::cout << "read buffer checking..." << std::endl;
    int bufferCheckRes = select(_sockFd + 1, &_readfds, NULL, NULL, NULL);

    if(bufferCheckRes == -1){
        std::cout << "read buffer check failed" << std::endl;
    }else if(bufferCheckRes == 0){
        std::cout << "read buffer check timeout" << std::endl;
    }else{
        //read from buffer
        char _buffer[MAX_CHAR_TO_READ] = {0};
        ssize_t bytesReceived = recv(_sockFd, _buffer, MAX_CHAR_TO_READ, 0);
        if(bytesReceived < 1){
            //server disconnected
            std::cout << "error to recv" << _buffer << std::endl;
            _connected = false;

        }else{
            std::cout << "received bytes: " << bytesReceived << std::endl;
            std::cout << "received message: " << _buffer << std::endl;
        }
    }
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
