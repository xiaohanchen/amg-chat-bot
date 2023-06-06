//
// Created by xiaohan on 23/05/2023.
//

#include <sys/socket.h>
#include <sys/event.h>
#include "../include/server_worker.h"

int ServerWorker::workerCount = 0;

ServerWorker::ServerWorker() {
    workerCount++;
    workerId = workerCount;
}

ServerWorker::~ServerWorker() {}

void ServerWorker::startRun() {

    //should have a switch for different multiplex IO:
    //select || epoll(linux) || kqueue(mac unix)
    _workerThread = new std::thread(&ServerWorker::_onRunSelect, this);
}


//select
void ServerWorker::_onRunSelect() {
    while(true){
        std::cout << getWorkerName() << " run select for clientNum=" << _connectedClients.size()<< std::endl;

        //todo check if there are new clients to be added

        //sleep if there is no new client
        if(_connectedClients.empty()){
            std::cout << "no connected client, sleep for 2s" << std::endl;
            sleep(2);
            continue;
        }

        //multiplex IO select todo  add from _clientsToBeAdded if not empty
        fd_set _readfds;
        FD_ZERO(&_readfds);
        int maxSocketFd = 0;
        for (const auto &item: _connectedClients){
            FD_SET(item.getConnectedSockFd(), &_readfds);
            maxSocketFd = std::max(maxSocketFd, item.getConnectedSockFd());
        }

        //select API to check if there is data in buffer
        int bufferCheckRes = select(maxSocketFd + 1, &_readfds, NULL, NULL, NULL);

        if(bufferCheckRes == -1){
            std::cout << "read buffer check failed" << std::endl;
            perror("select failed:");
            //todo get error code
            sleep(5);
        }else if(bufferCheckRes == 0){
            std::cout << "read buffer check timeout" << std::endl;
        }else{
            //recv from rBuffer if ready
            for (auto it = _connectedClients.begin(); it != _connectedClients.end();) {
                int _socketFdTemp = it->getConnectedSockFd();
                if(FD_ISSET(_socketFdTemp, &_readfds)){
                    char * recvFromBuffer = it->recvFromBuffer();
                    if(!recvFromBuffer){
                        //client diconnected, need to be removed
                        std::cout << "client disconnected, socket=" << it->getConnectedSockFd() << std::endl;
                        _connectedClients.erase(it);
                        //since erased, it++ not required
                        continue;
                    }
                    delete recvFromBuffer;
                }
                it++;
            }

        }

        //extra stuff ... e.g.heartbeat
    }


}

bool ServerWorker::isAvailable() {
    return MAX_CLIENT_NUM_PER_WORKER > _connectedClients.size();
}

void ServerWorker::addConnectedClient(const ConnectedClient &connectedSockFd) {
    _connectedClients.push_back(connectedSockFd);
}

std::string ServerWorker::getWorkerName() {
    return "WORKER" + std::to_string(workerId);
}

void ServerWorker::_onRunKqueue() {

    //create kqueue instance
    int kq = kqueue();

    //create event list, and


    while(true){
        //sleep if there is no new client
        if(_connectedClients.empty()){
            std::cout << "no connected client, sleep for 2s" << std::endl;
            sleep(2);
            continue;
        }

        //multiplex IO kqueue:

        //register client connections for read event
        for (const auto &item: _connectedClients){
            struct kevent event;
            //initialize event
            EV_SET(&event, item.getConnectedSockFd(), EVFILT_READ, EV_ADD, 0, 0, NULL);
            //add to kqueue
            kevent(kq, &event, 1, NULL, 0, NULL);
        }

        //event
        struct kevent eventReceived[_connectedClients.size()];
        int n = kevent(kq, NULL, 0, eventReceived, _connectedClients.size(), NULL);
        for (int i = 0; i <n; ++i) {
            int clientFd = eventReceived[i].ident;
            //found client connection and recev bytes from buffer
            //todo

        }
    }








}




