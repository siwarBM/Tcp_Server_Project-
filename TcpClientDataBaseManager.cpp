#include "TcpClientDataBaseManager.h"
#include "TcpServerController.h"
#include <list>
#include <iostream>
class tcp_client;

TcpClientDataBaseManager::TcpClientDataBaseManager(TcpServerController
 *tcp_server)
{
    std::cout << "tcp_server= " << this->tcp_server << std::endl;
    this->tcp_server = tcp_server;
}

TcpClientDataBaseManager::~TcpClientDataBaseManager()
{

}
void TcpClientDataBaseManager::StartClientDataBaseInit()
{

}
void TcpClientDataBaseManager::AddClinetToDataBase(tcp_client *tcpclient)
{
    printf("push_back NewClient\n");
    this->tcp_client_db.push_back(tcpclient);

}

void TcpClientDataBaseManager::DisplayClientDataBase()
{
    tcp_client *tcpclient;
    std::list<tcp_client *>::iterator it;
    std::cout << "starting DisplayClientDataBase"<< std::endl;
    for(it=this->tcp_client_db.begin(); it!=this->tcp_client_db.begin(); ++it)
    {
        std::cout << "tcpclient data base loop "<< std::endl;
        tcpclient = *it;
        std::cout << "tcpclient= " << tcpclient<< std::endl;
        tcpclient->Display();
    }

    std::cout << "Display client data base"<< std::endl;
}