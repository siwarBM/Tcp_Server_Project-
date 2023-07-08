#include "TcpClientDataBaseManager.h"
#include "TcpServerController.h"
#include <list>

class tcp_client;

TcpClientDataBaseManager::TcpClientDataBaseManager(TcpServerController
 *tcp_server)
{
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
    this->tcp_client_db.push_back(tcpclient);

}

void TcpClientDataBaseManager::DisplayClientDataBase()
{
    tcp_client *tcpclient;
    std::list<tcp_client *>::iterator it;
    for(it=this->tcp_client_db.begin(); it!=this->tcp_client_db.begin(); ++it)
    {
        tcpclient = *it;
        tcpclient->Display();
    }
}