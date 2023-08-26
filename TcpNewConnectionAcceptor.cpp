#include <winsock2.h>
#include <ws2tcpip.h>
#include <ws2spi.h>
#include <memory.h>
#include <iostream>
using namespace std;
#include "TcpNewConnectionAcceptor.h"
#include "TcpServerController.h"
#include "network_utils.h"
#include "tcp_client.h"

// Define the constructor for TcpNewConnectionAcceptor class.
TcpNewConnectionAcceptor::TcpNewConnectionAcceptor(TcpServerController *tcp_server)
 {
    // here we have only one member *tcp_server is a pointer to tcpservercontroller instance.
    this->tcp_server = tcp_server;
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cout << "Failed to initialize Winsock" << std::endl;
    }

    // need to use socket call system to get the file descriptor.
    this->accept_filed =socket(AF_INET , SOCK_STREAM , IPPROTO_TCP);

    if (this->accept_filed == INVALID_SOCKET) {
        std::cout << "Failed to create socket. Error code: " << WSAGetLastError() << std::endl;
    }

    std::cout << "Socket Created" << std::endl;

    std::cout << "accept_new_connexion_thread" << std::endl;

    // Start thread for listening to the new connexions.
    this->accept_new_connexion_thread = (pthread_t *) calloc(1,sizeof(pthread_t));
 }
 // Destructor function.
 TcpNewConnectionAcceptor::~TcpNewConnectionAcceptor() {
        // Properly clean up and release resources

        // Close the socket
        closesocket(this->accept_filed);

        // Clean up the thread object
        if (accept_new_connexion_thread != nullptr) {
            pthread_join(*accept_new_connexion_thread, NULL);
            delete accept_new_connexion_thread;
            accept_new_connexion_thread = nullptr;
        }

        // Cleanup Winsock
        WSACleanup();
    }

 /*create an infinity loop
 invoke accept() system call to accept new connections.
 Notify the application for new connections.*/

void TcpNewConnectionAcceptor::StartTcpNewConnectionAcceptorThreadInternal()
{
    WSADATA wsaData;
    int ex = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (ex != 0) {
        std::cout << "WSAStartup failed: in start internal threads" << std::endl;
    }
    this->accept_filed = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (this->accept_filed == INVALID_SOCKET) {
        std::cout << "Failed to create socket. Error code: " << WSAGetLastError() << std::endl;
    }

    int opt = 1;
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(this->tcp_server->ip_addr);
    server_addr.sin_addr.s_addr = htonl(this->tcp_server->ip_addr);

    if (setsockopt(this->accept_filed, SOL_SOCKET, SO_REUSEADDR, (char*)&opt, sizeof(opt)) < 0)
    {
        std::cout << "setsockopt Failed" << std::endl;
    }


    /* bind the socket */
    std::cout << "Call bind function" << std::endl;

    if (bind(this->accept_filed, (struct sockaddr*)&server_addr, sizeof(struct sockaddr)) == -1)
    {
        std::cout << "fail in bind function so exit" << std::endl;
        std::cout << "Error : Acceptor socket bind failed [" << network_convert_ip_n_to_p(this->tcp_server->ip_addr, 0)
            << "(0x" << std::hex << tcp_server->ip_addr << "), " << std::dec << tcp_server->no_port << "], error=" << errno << std::endl;
    }

    std::cout << "Call listen Api\n" << std::endl;
        // LISTEN;
    if (listen(this->accept_filed, SOMAXCONN) < 0)
    {
        std::cout << "listen failed" << std::endl;
    }
    // Set the listening socket to non-blocking mode using ioctlsocket
    u_long mode = 1;
    ioctlsocket(this->accept_filed, FIONBIO, &mode);
        std::cout <<"listen API execute succ" << std::endl;
        struct sockaddr_in client_addr;
        socklen_t addr_len = sizeof(client_addr);
        SOCKET comm_sock_fd;
    while (true)
    {
        comm_sock_fd = accept(this->accept_filed, (struct sockaddr*)&client_addr, &addr_len);
        if (comm_sock_fd == INVALID_SOCKET)
        {
            std::cout << "Error in accepting new connections" << std::endl;
            // Log the error or handle it in an appropriate manner
            continue;
        }

        std::cout << "create a tcp client object" << std::endl;
        // Need to create a tcp client object.
        tcp_client* tcpclient = new tcp_client(client_addr.sin_addr.s_addr, client_addr.sin_port);
        tcpclient->tcp_server = this->tcp_server;
        tcpclient->comm_df = comm_sock_fd;

        std::cout << " check tcp_client connected" << std::endl;
        if (this->tcp_server->client_connected)
        {
            this->tcp_server->client_connected(tcp_server, tcpclient);
        }

        std::cout << "Need to tell the TcpController to further process the Client" << std::endl;
        // Need to tell the TcpController to further process the Client.
        this->tcp_server->ProcessNewClient(tcpclient);

        std::cout << "Connection Accepted from Client [" << network_convert_ip_n_to_p(htonl(client_addr.sin_addr.s_addr), 0) << ", " << htons(client_addr.sin_port) << "]" << std::endl;
    }
    // Cleanup: Close the socket
    closesocket(this->accept_filed);
    // Cleanup Winsock
    WSACleanup();
}

static void* tcp_listen_for_new_connections(void*arg) // search about pointer function.
 {
    std::cout << "Start listening to new connections"<< std::endl;
    TcpNewConnectionAcceptor *tcp_new_conn_acc =
    (TcpNewConnectionAcceptor *)arg;
    tcp_new_conn_acc->StartTcpNewConnectionAcceptorThreadInternal();
 }

 // This function will Start the connection Acceptor source thread.
 /*start thread.*/
 void TcpNewConnectionAcceptor::StartTcpNewConnectionAcceptorThread() // arg is the object of that class
 {
    // tcp_listen_for_new_connexion : callback function using with this thread.
    if(pthread_create(this->accept_new_connexion_thread, NULL, tcp_listen_for_new_connections,(void*)this)) // This is the object of new connector class.
    {
        std::cout << "Thread creation failed\n"<< endl;
    }
    std::cout << "Service Start" << endl;
 }