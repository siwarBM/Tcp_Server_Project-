#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <string>

#pragma comment(lib, "ws2_32.lib")

// Convert a network (binary) IP address to a presentation (textual) IP address.
char * network_convert_ip_n_to_p(uint32_t ip_addr, char *output_buffer) {
    //char output_buffer[16];
    snprintf(output_buffer, sizeof(output_buffer), "%u.%u.%u.%u",
        (ip_addr >> 24) & 0xFF,
        (ip_addr >> 16) & 0xFF,
        (ip_addr >> 8) & 0xFF,
        ip_addr & 0xFF);

    return output_buffer;
}

// Convert a textual IP address to its binary form.
uint32_t network_covert_ip_p_to_n(const char *ip_addr) {
    uint32_t binary_prefix = inet_addr(ip_addr);
    if (binary_prefix == INADDR_NONE) {
        std::cout << "ERROR: Invalid IP address\n" << std::endl;
    }
    return ntohl(binary_prefix);
}

/*int main() {
    If you wanna to test the network_convert_ip_p_to_n and network_convert_ip_n_to_p, you can test using the following main function.
    uint32_t ip_addr_n = network_convert_ip_p_to_n("192.168.1.1");
    std::cout << "Binary IP: " << std::hex << ip_addr_n << std::endl;

    std::string ip_addr_p = network_convert_ip_n_to_p(ip_addr_n);
    std::cout << "Textual IP: " << ip_addr_p << std::endl;

    return 0;
}
*/