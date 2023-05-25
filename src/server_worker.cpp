//
// Created by xiaohan on 23/05/2023.
//

#include <sys/socket.h>
#include "../include/server_worker.h"


ServerWorker::ServerWorker() {
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
        std::cout << "run select ..." << std::endl;

        //todo check if there are new clients to be added

        //sleep if there is no new client
        if(_connectedClients.empty()){
            std::cout << "no connected client, sleep for 2s" << std::endl;
            sleep(2);
            continue;
        }

        //multiplex IO

        //select
        fd_set _readfds;
        FD_ZERO(&_readfds);
        int maxSocketFd = 0;
        for (const auto &item: _connectedClients){
            FD_SET(item.getConnectedSockFd(), &_readfds);
            maxSocketFd = std::max(maxSocketFd, item.getConnectedSockFd());
        }
        int bufferCheckRes = select(maxSocketFd + 1, &_readfds, NULL, NULL, NULL);
        if(bufferCheckRes == -1){
            std::cout << "read buffer check failed" << std::endl;
        }else if(bufferCheckRes == 0){
            std::cout << "read buffer check timeout" << std::endl;
        }else{
            //recv from rBuffer if ready
            for (auto it = _connectedClients.begin(); it != _connectedClients.end();) {
                int _socketFdTemp = it->getConnectedSockFd();
                if(FD_ISSET(_socketFdTemp, &_readfds)){
                    char * recvFromBuffer = it->recvFromBuffer();

//                    if(!recvFromBuffer){
//                        //client diconnected, need to be removed
//                        //todo remove can be expensive, could be exhanced
//                        _connectedClients.erase(it);
//                    }
//                    delete recvFromBuffer;

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




