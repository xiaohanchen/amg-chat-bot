# amg-chat-bot
performance server based on native socket api programming for training purpose

implemented in cases:-
- BIO, thread for each connection(see branch xiaohan/socketConnectFromMain)
- NIO
  - select(see main branch)
  - kqueue (mac env)
  - epoll (linux env)

## Structure
**ChatServer.class** and **ChatClient.class** are the main classes for managing lifecycle of server and client. 

there are multiple **ServerWorker** instances in ChatServer, each of which is responsible for checking R/W buffer of **ConnectedClient**.

## Configuration
1. 'constants.h.COMMUNICATION_TYPE' to switch between BIO and NIO 
2. 'constants.h.MAX_CLIENT_NUM_PER_WORKER' to set max client number per worker thread
3. TBC

## Examples
this project use LOCALHOST to run test, but starting examples in multiple hosts are supported too. 
1. start 'server_test.cpp' will open a socket and listen for clients' connections; 
2. start 'client_test.cpp' to create multiple clients 


## Future Plan
1. add TCP support to avoid packet fragmentation issue 
2. integrate Disruptor to further improve performance (https://github.com/Abc-Arbitrage/Disruptor-cpp)
3. docker support so that can build linux in mac env
4. CLI support to control server and client
5. integrate google benchmark (https://github.com/google/benchmark)

## BenchMark
TPS = NUMBER_OF_CLIENTS / CLIENT_MSG_SEND_INTERVAL

### IO:SELECT
#### [1 WORKER THREAD]
650 clients connection=> 350TPS
beyond this: error to select from fileDescSet
goal: 1024 TPS (select)

#### [10 WORKER THREADS * 100 CLIENTS PER THREAD]
10000 clients connection=> 5000TPS

### IO:KQUEUE



