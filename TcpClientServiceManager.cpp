#include "TcpClientServiceManager.h"
#include "TcpServerController.h"
#include <iostream>

// Define the constructor for TcpClientServiceManager.
TcpClientServiceManager::TcpClientServiceManager(TcpServerController
 *tcp_server)
{
     this->tcp_server = tcp_server;
}

TcpClientServiceManager::~TcpClientServiceManager()
{
}

void TcpClientServiceManager::StartTcpClientServiceManagerThread()
{
    /* Run thread in Infinity loop.
       Listen for all data requests for all the client connected.*/
}
void TcpClientServiceManager::ClientFDStartListen(tcp_client *tcpclient)
{
     std::cout << "do nothing need to implement it" << std::endl;
}