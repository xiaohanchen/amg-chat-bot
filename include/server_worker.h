//
// Created by xiaohan on 23/05/2023.
//

#ifndef AMG_CHAT_BOT_SERVER_WORKER_H
#define AMG_CHAT_BOT_SERVER_WORKER_H

#include "connected_client.h"
#include "constants.h"

class ServerWorker {

private:
    //managed connections
    ConnectedClient _connectedClients[MAX_CLIENT_NUM_PER_WORKER];

public:
    ServerWorker();
    ~ServerWorker();

    /**
     * add a new connected client
     * @param connectedSockFd
     */
    void addConnectedClient(int connectedSockFd);

    /**
     * start a thread to check _connectedClients to see if there is any data to be read
     * read if there is one
     * proceed in multiplex manner
     */
    void startRun();


};


#endif //AMG_CHAT_BOT_SERVER_WORKER_H
