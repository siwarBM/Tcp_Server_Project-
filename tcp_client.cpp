#include "tcp_client.h"
#include "TcpServerController.h"
#include "network_utils.h"

#include <stdint.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <ws2spi.h>


tcp_client::tcp_client(uint32_t ip_addr, uint16_t port_number)
{
    this->ip_addr = ip_addr;
    this->port_number = port_number;
}

tcp_client::~tcp_client()
{
}

void tcp_client::Display()
{
    setbuf(stdout, NULL);
    printf("Tcp Client : [%s,%d] ref count = %;d\n ref cout = %d\n",
            network_convert_ip_n_to_p(htonl(this->ip_addr),0),
            htons(this->port_number));
}

