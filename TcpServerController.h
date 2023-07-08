#ifndef TCPServerController_H
#define TCPServerController_H

#include <string>
#include <stdint.h>
#include "tcp_client.h"
using namespace std;

class TcpNewConnectionAcceptor;
class TcpClientServiceManager;
class TcpClientDataBaseManager;
class tcpclient;

class TcpServerController
{
private:
    // Pointers to the following instances.
    TcpNewConnectionAcceptor *tcp_new_connexion_acc;
    TcpClientServiceManager *tcp_service_manager;
    TcpClientDataBaseManager *tcp_client_data_base;
    /* data */
public:
    uint32_t ip_addr;
    uint16_t no_port;
    string name;

    //fUNCTION POINTER;
    void(*client_connected)(const TcpServerController* , const tcp_client* );
    void(*client_disconnected)(const TcpServerController* , const tcp_client* );
    void(*client_msg_rsvd)(const TcpServerController* , const tcp_client*, unsigned char *, uint16_t);
    void setServerNotificationCallbacks(
                        void(*client_connected)(const TcpServerController* , const tcp_client* ),
                        void(*client_disconnected)(const TcpServerController* , const tcp_client* ),
                        void(*client_msg_rsvd)(const TcpServerController* , const tcp_client*, unsigned char *, uint16_t));
    // Define constructor and Destructor.
    TcpServerController(std::string ip_addr,uint16_t no_port, string name);
    // Will use it as a pointer to the function this prototype.
    ~TcpServerController();

    // Start Tcp server and initialize all needed services.
    void start();
    void stop();
    void ProcessNewClient(tcp_client *tcpclient);
    void Display();
};

// declarations go here

#endif // MY_HEADER_FILE_H