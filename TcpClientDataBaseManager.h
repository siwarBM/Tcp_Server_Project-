#ifndef TCPClientDataBaseManager_H
#define TCPClientDataBaseManager_H
#include "tcp_client.h"
#include <list>

class TcpServerController;

// declarations go here
class TCpClient;
class TcpClientDataBaseManager
{
private:
    /* data */
    // List of connected tcpclient.
    std::list<tcp_client*> tcp_client_db; 

public:
    TcpServerController *tcp_server;
    TcpClientDataBaseManager(TcpServerController *);
    ~TcpClientDataBaseManager();
    void StartClientDataBaseInit();
    void AddClinetToDataBase(tcp_client *tcpclient);
    void DisplayClientDataBase();
};
#endif // MY_HEADER_FILE_H