#ifndef __TCP_Client__
#define __TCP_Client__
#include <stdint.h>
class TcpServerController;
class tcp_client
{
private:
public:
        /* data */
    uint32_t ip_addr;
    uint16_t port_number;
    int comm_df;
    TcpServerController *tcp_server;
    tcp_client(uint32_t ip_addr, uint16_t port_number);
    ~tcp_client();
    void Display();
};
#endif
