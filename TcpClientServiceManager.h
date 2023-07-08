#ifndef TCPClientServiceManager_H
#define TCPClientServiceManager_H

class TcpServerController;
class tcp_client;
// declarations go here
class TcpClientServiceManager
{
private:
    /* data */
public:
    TcpServerController *tcp_server;
    TcpClientServiceManager(TcpServerController *);
    ~TcpClientServiceManager();
    void StartTcpClientServiceManagerThread();
    void ClientFDStartListen(tcp_client *tcpclient);
};
#endif // MY_HEADER_FILE_H