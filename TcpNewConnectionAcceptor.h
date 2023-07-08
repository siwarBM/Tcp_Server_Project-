#ifndef TCPNewConnectionAcceptor_H
#define TCPNewConnectionAcceptor_H

#include <pthread.h>

class TcpServerController;
class TCpClient;
// declarations go here
class TcpNewConnectionAcceptor
{
private:
    /* data */
    int accept_filed;
    // Will use it to listen if there is new client'connexion.
    pthread_t *accept_new_connexion_thread;
public:
    TcpServerController *tcp_server;
    TcpNewConnectionAcceptor(TcpServerController *);
    ~TcpNewConnectionAcceptor();
    void StartTcpNewConnectionAcceptorThread();
    void StartTcpNewConnectionAcceptorThreadInternal();
};
#endif // MY_HEADER_FILE_H