//
// Created by xiaohan on 23/05/2023.
//

#ifndef AMG_CHAT_BOT_SERVER_WORKER_H
#define AMG_CHAT_BOT_SERVER_WORKER_H

#include "connected_client.h"
#include "constants.h"
//#include "sys/epoll.h" mac doesnt support epoll, only linux
#include <sys/event.h>
//#include "sys/kqueue.h"
#include "unistd.h"
#include <thread>

class ServerWorker {

private:
    //managed connections
    std::vector<ConnectedClient> _connectedClients;

    //connections to be added to "_connectedClients"
    std::vector<ConnectedClient> _clientsToBeAdded;

    //mutex for _clientsToBeAdded (server & worker race condition)
    std::mutex _mutex;

    //background thread to check if there is data to be read
    std::thread* _workerThread = nullptr;

    //if the clients array changes
    bool _clientsChange = false;

    //worker count
    static int workerCount;

    //id
    int workerId;

    //readFds for select
    fd_set _readfds;
    /**
     * where multiplexing happens
     * select IO for _connectedClients
     */
    void _onRunSelect();

    /**
     * epoll IO for _connectedClients
     */
    void _onRunEpoll();

    /**
     * kqueue IO for _connectedClients
     */
    void _onRunKqueue();

public:
    ServerWorker();
    ~ServerWorker();

    /**
     * add a new connected client
     * @param connectedSockFd
     */
    void addConnectedClient(const ConnectedClient& connectedSockFd);

    /**
     * start a thread to check _connectedClients to see if there is any data to be read
     * read if there is one
     * proceed in multiplex manner
     */
    void startRun();

    /**
     * check if worker is able to accept new connections
     * @return
     */
    bool isAvailable();

    /**
     * WORKER_<workerCount>
     * @return
     */
    std::string getWorkerName();

};


#endif //AMG_CHAT_BOT_SERVER_WORKER_H
