#include <iostream>
using namespace std;
#include "TcpServerController.h"
#include "TcpClientDataBaseManager.h"
#include "TcpClientServiceManager.h"
#include "TcpNewConnectionAcceptor.h"
#include "network_utils.h"
#include "TCpClient.h"

static void prirnt_client(const tcp_client *tcpclient)
{

    /*The htons function is used to convert a 16-bit (2-byte) short 
    
    integer value from host byte order to network byte order.*/

    /*The htonl function, is used to convert a 32-bit (4-byte) 
    long integer value from host byte order to network byte order.*/

    printf("[%s,%d]\n",network_convert_ip_n_to_p(htonl(tcpclient->ip_addr),0),htons(tcpclient->port_number));

}

static void prirnt_server(const TcpServerController *tcpserver)
{

    printf("[%s,%d]\n",network_convert_ip_n_to_p(htonl(tcpserver->ip_addr),0),htons(tcpserver->no_port));

}
static void app_client_connected(const TcpServerController* tcp_server, const tcp_client* tcpclient)
{
    prirnt_server(tcp_server);
    prirnt_client(tcpclient);
    printf("app_Client : Client Connected");

}
static void app_client_disconnected(const TcpServerController* , const tcp_client* )
{

}
static void client_msg_rsvd(const TcpServerController* , const tcp_client*, unsigned char *, uint16_t)
{

}
int main(int argc, char **argv)
{
    // Create an instance of class TcpServerController.
   // std::cout << "Just Test" <<endl;
    TcpServerController *server_controller = new TcpServerController("127.0.0.1",30000, "Default Siwar");
    //std::cout << "001 Just Test" <<endl;
    // Call the start method.
    server_controller->setServerNotificationCallbacks(app_client_connected, app_client_disconnected, client_msg_rsvd);
    server_controller->start();
   // std::cout << "002 Just Test" <<endl;
    scanf("\n");
    //cout << "Just Test" <<endl;
    server_controller->Display();
    return 0;
}