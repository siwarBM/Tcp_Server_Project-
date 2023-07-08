#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0600
#elif _WIN32_WINNT < 0x0600
#undef _WIN32_WINNT
#define _WIN32_WINNT 0x0600
#endif

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <ws2spi.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <memory.h>
#include "network_utils.h"
#include <stdint.h>

#pragma comment(lib, "ws2_32.lib")  // Winsock Library

/*char *
network_convert_ip_n_to_p(uint32_t ip_addr,
                    char *output_buffer){

    char* out = output_buffer ? output_buffer : new char[16];
    memset(out, 0, 16);
    ip_addr = htonl(ip_addr);

    // Convert an IPv4 address from binary to text form.
    sprintf(out, "%u.%u.%u.%u",
        (ip_addr >> 24) & 0xFF,
        (ip_addr >> 16) & 0xFF,
        (ip_addr >> 8) & 0xFF,
        ip_addr & 0xFF);

    return out;
}*/

char* network_convert_ip_n_to_p(uint32_t ip_addr, char* output_buffer) {
    char* out = output_buffer ? output_buffer : new char[16];
    memset(out, 0, 16);

    sprintf(out, "%u.%u.%u.%u",
        (ip_addr >> 24) & 0xFF,
        (ip_addr >> 16) & 0xFF,
        (ip_addr >> 8) & 0xFF,
        ip_addr & 0xFF);

    return out;
}

// Convert a textual IP address to its binary form.
uint32_t 
network_covert_ip_p_to_n(const char* ip_addr) {
    uint32_t binary_prefix = inet_addr(ip_addr);
    if (binary_prefix == INADDR_NONE) {
        printf("ERROR: Invalid IP address");
        return 0;
    }
    return htonl(binary_prefix);
}