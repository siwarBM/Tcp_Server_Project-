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
   // std::cout<<"tcp new connection acceptor"<< endl;
    // here we have only one member *tcp_server is a pointer to tcpservercontroller instance.
    this->tcp_server = tcp_server;
   // std::cout<<" 001 tcp new connection acceptor"<< endl;
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        setbuf(stdout, NULL);
        printf("Failed to initialize Winsock.\n");
        //return 1; // or handle the error appropriately
    }

    // need to use socket call system to get the file descriptor.
    this->accept_filed =socket(AF_INET , SOCK_STREAM , IPPROTO_TCP);
    //std::cout<<" 002 tcp new connection acceptor"<< endl;
    if (this->accept_filed == INVALID_SOCKET) {
        setbuf(stdout, NULL);
        printf("Failed to create socket. Error code: %d\n", WSAGetLastError());
        //
        //std::cout << "Failed to create soket siwar."<< endl;
        // return 1; // or handle the error appropriately
    }

    if(this->accept_filed < 0)
    {
        //std::cout<<" 003 tcp new connection acceptor"<< endl;
        setbuf(stdout, NULL);
        printf("Error: File Des not created.");
        //exit(0);
    }
    //std::cout<<" 004 tcp new connection acceptor"<< endl;
    this->accept_new_connexion_thread = (pthread_t *) calloc(1,sizeof(pthread_t)); // Start thread for listening to new connexion.
 }
 // Destructor function.
 TcpNewConnectionAcceptor::~TcpNewConnectionAcceptor()
 {}

 /*create an infinity loop
 invoke accept() system call to accept new connections.
 Notify the application for new connections.*/

void TcpNewConnectionAcceptor::StartTcpNewConnectionAcceptorThreadInternal()
{
    this->accept_filed;
    // Used to accept connexion. it's the same code always used.
    int opt = 1;
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(this->tcp_server->ip_addr);
    server_addr.sin_addr.s_addr = htonl(this->tcp_server->ip_addr);

    if(setsockopt(this->accept_filed, SOL_SOCKET,
                SO_REUSEADDR, (char*)&opt,sizeof(opt))<0)
        {
            setbuf(stdout, NULL);
            printf("setsockopt Failed\n");
            perror("info error 1");
            exit(1);
        }

    /*if(setsockopt(this->accept_filed, SOL_SOCKET,
                SO_RE, (char*)&opt,sizeof(opt))<0)
        {
            printf("setsockopt Failed\n");
            exit(0);
        }*/

        /* bind the socket */

        if(bind(this->accept_filed, (struct sockaddr *)&server_addr,
                sizeof(struct sockaddr)) == -1 )

        {
            // Means that tcp server not ready to accept new connexion.
            /* data */
            setbuf(stdout, NULL);
            printf("Error : Acceptor socket bind failed [%s(0x%x), %d], error=%d\n",
            network_convert_ip_n_to_p(this->tcp_server->ip_addr,0),
            tcp_server->ip_addr, tcp_server->no_port, errno
            );
            perror("info error 2");
            exit(1);
        }

        // LISTEN;
        if(listen(this->accept_filed,5) < 0)
        {
            setbuf(stdout, NULL);
            printf("listen failed\n");
            perror("info error 3");
            exit(1);
        }

        struct sockaddr_in client_addr;
        socklen_t addr_len = sizeof(client_addr);
        int comm_sock_fd;

        while(true)
        {
            // Communication socket file.
            comm_sock_fd = accept(this->accept_filed,
                                 (struct sockaddr *)&client_addr, &addr_len);

            // Once tcp server gets an error while listen just show an error message
            // and continue.
            if( comm_sock_fd < 0)
            {
                setbuf(stdout, NULL);
                printf("Error in accepting new connections\n");
                continue;
            }

            // Need to create a tcp client object.
            tcp_client *tcpclient = new tcp_client(client_addr.sin_addr.s_addr,client_addr.sin_port);
            tcpclient->tcp_server = this->tcp_server;
            tcpclient->comm_df = comm_sock_fd;
            if(this->tcp_server->client_connected)
            {
                this->tcp_server->client_connected(tcp_server,tcpclient);
            }
            // Need to tell the TcpController to further process the Client.
            this->tcp_server->ProcessNewClient(tcpclient);
            setbuf(stdout, NULL);
            printf("Connection Acceptted from Client [%s, %d]\n",
                    network_convert_ip_n_to_p( htonl(client_addr.sin_addr.s_addr),0), htons(client_addr.sin_port));

            // Listeining Again.
        }
        
        
    
}

static void* tcp_listen_for_new_connections(void*arg) // search about pointer function.
 {
    //std::cout << "start the tcp listen for new connections" << endl;
    printf("Just starting new connexion");
    TcpNewConnectionAcceptor *tcp_new_conn_acc =
    (TcpNewConnectionAcceptor *)arg;
    tcp_new_conn_acc->StartTcpNewConnectionAcceptorThreadInternal();
 }

 // This function will Start the connection Acceptor source thread.
 // Accept connexion from new client. // Please search about calloc method and why we need it.
 // Search about multithreading in freebootcamp, may you find somthing usefulll .. 
 /*start thread.*/
 void TcpNewConnectionAcceptor::StartTcpNewConnectionAcceptorThread() // arg is the object of that class
 {
    // tcp_listen_for_new_connexion : callback function using with this thread.
    if(pthread_create(this->accept_new_connexion_thread, NULL, tcp_listen_for_new_connections,(void*)this)) // This is the object of new connector class.
    {
        setbuf(stdout, NULL);
        printf("%s() Thread creation failed error=%d\n", __FUNCTION__,errno);
        //exit(0);
    }
    setbuf(stdout, NULL);
    printf("Service Started: %s()\n", __FUNCTION__);

 }