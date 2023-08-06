#include <iostream>
#include <memory>
#include "TcpServerController.h"
#include "TcpClientDataBaseManager.h"
#include "TcpClientServiceManager.h"
#include "TcpNewConnectionAcceptor.h"
#include "network_utils.h"

static void print_client(const tcp_client* tcpclient)
{
    std::cout << "[" << network_convert_ip_n_to_p(htonl(tcpclient->ip_addr), 0) << "," << htons(tcpclient->port_number) << "]" << std::endl;
}

static void print_server(const TcpServerController* tcpserver)
{
    std::cout << "[" << network_convert_ip_n_to_p(htonl(tcpserver->ip_addr), 0) << "," << htons(tcpserver->no_port) << "]" << std::endl;
}

static void app_client_connected(const TcpServerController *tcp_server, const tcp_client * tcpclient)
{
    print_server(tcp_server);
    print_client(tcpclient);
    std::cout << "app_Client : Client Connected" << std::endl;
}

static void app_client_disconnected(const TcpServerController * , const tcp_client *)
{
    // Do nothing for now.
}

static void client_msg_rsvd(const TcpServerController* , const tcp_client*, unsigned char *, uint16_t)
{
    // Do nothing for now.
}

int main()
{
    // Create an instance of class TcpServerController.
    std::unique_ptr<TcpServerController> server_controller = std::make_unique<TcpServerController>("127.0.0.1", 40000, "Default Siwar");
    // Call the start method.
    server_controller->setServerNotificationCallbacks(app_client_connected, app_client_disconnected, client_msg_rsvd);
    server_controller->start();
    server_controller->Display();

    return 0;
}
