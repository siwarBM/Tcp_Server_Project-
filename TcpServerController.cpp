#include "TcpServerController.h"
#include "TcpClientDataBaseManager.h"
#include "TcpNewConnectionAcceptor.h"
#include "TcpClientServiceManager.h"
#include "network_utils.h"

#include <stdio.h>
#include <assert.h>
using namespace std;
#include <iostream>
#include "network_utils.h"
#include "tcp_client.h"



// TcpServerController Constructor.
TcpServerController::TcpServerController(std::string ip_addr, uint16_t port_number, std::string name)
{
    std::cout << "start tcp server controller" << endl;
    this->ip_addr = network_covert_ip_p_to_n(ip_addr.c_str());
    std::cout << "this->ip_addr=" << this->ip_addr << endl;
    this->no_port = port_number;
    std::cout << "this->no_port= " << this->no_port << endl;
    this->name = name;

    std::cout << "name="<< this->name << endl;

    this->tcp_client_data_base = new TcpClientDataBaseManager(this);
    std::cout << "this->tcp_client_data_base" << endl;
    this->tcp_new_connexion_acc = new TcpNewConnectionAcceptor(this);
    std::cout << "this->tcp_new_connexion_acc" << endl;
    this->tcp_service_manager = new TcpClientServiceManager(this);
    std::cout << "this->tcp_service_manager" << endl;
}

void TcpServerController::start()
{
    //std::cout << "starting function"<<endl;
    // Need to initialize the db structure.
    // Start the CRS thread. ( new_connexion acceptor ).
    // Start the DRS thread. ( servicemanager ).
    this->tcp_new_connexion_acc->StartTcpNewConnectionAcceptorThread(); // Need to implement this method.
    //std::cout << "001 starting function"<<endl;
    this->tcp_service_manager->StartTcpClientServiceManagerThread();
    //std::cout << "002 starting function"<<endl;
    this->tcp_client_data_base->StartClientDataBaseInit();
    //std::cout << "003 starting function **"<<endl;
    std::cout << "Tcp Server is Up and Running " << network_convert_ip_n_to_p(this->ip_addr, 0) << "port no " << this->no_port << std::endl;
    }

// Make TCP Server listen to make new connection.
// new conections are accepted using accept syscall.
/* we need to create accept_fd  (accept file descript) using socket*/

void
TcpServerController::ProcessNewClient(tcp_client *tcpclient)
{
    /* Tcpservercontroller has to request the client data manager.
      to store this new data client object. In the Internal dataBase.
    */
   
    std::cout << "Process NewClient" << std::endl;
    this->tcp_client_data_base->AddClinetToDataBase(tcpclient);
    
    std::cout << " Manager must Start Listen" << std::endl;
    // Manager must to start listeining in the communication socket of the new tcpclient.
    this->tcp_service_manager->ClientFDStartListen(tcpclient);
}
void 
TcpServerController::setServerNotificationCallbacks(
                        void(*client_connected)(const TcpServerController* , const tcp_client* ),
                        void(*client_disconnected)(const TcpServerController* , const tcp_client* ),
                        void(*client_msg_rsvd)(const TcpServerController* , const tcp_client*, unsigned char *, uint16_t))
    {
        this->client_connected = client_connected;
        this->client_disconnected = client_disconnected;
        this->client_msg_rsvd = client_msg_rsvd;
         

                        
    }
void TcpServerController::Display()
{

    std::cout << "Server Name " << this->name.c_str() << std::endl;
    std::cout << "Listening on : " << network_convert_ip_n_to_p(this->ip_addr,0) << " port no " << this->no_port << std::endl;
    this->tcp_client_data_base->DisplayClientDataBase();

}
TcpServerController::~TcpServerController() {
    // Destructor implementation
    // Clean up any resources, if needed
}
// Note : This application involve multiClient Connexion.