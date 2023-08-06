#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>

#pragma comment(lib, "ws2_32.lib")

// Define the server's IP address and port here or allow the user to input them as arguments
#define DEST_PORT 40000
#define SERVER_IP_ADDRESS "127.0.0.1"

typedef struct _test_struct {
    uint16_t msg_size;
    unsigned int a;
    unsigned int b;
} test_struct_t;

typedef struct result_struct_ {
    unsigned int c;
} result_struct_t;

void setup_tcp_communication() {
    WSADATA wsaData;
    int ex = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (ex != 0) {
        std::cerr << "WSAStartup failed." << std::endl;
        exit(1);
    }

    SOCKET sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sockfd == INVALID_SOCKET) {
        std::cerr << "Failed to create socket. Error code: " << WSAGetLastError() << std::endl;
        WSACleanup();
        exit(1);
    }

    struct sockaddr_in dest;
    dest.sin_family = AF_INET;
    dest.sin_port = htons(DEST_PORT);
    dest.sin_addr.s_addr = inet_addr(SERVER_IP_ADDRESS);

    if (connect(sockfd, (struct sockaddr*)&dest, sizeof(dest)) == SOCKET_ERROR) {
        std::cerr << "Connection failed. Error code: " << WSAGetLastError() << std::endl;
        closesocket(sockfd);
        WSACleanup();
        exit(1);
    }

    test_struct_t client_data[2];
    result_struct_t result;

    while (true) {
        std::cout << "Enter a1: ";
        std::cin >> client_data[0].a;
        std::cout << "Enter b1: ";
        std::cin >> client_data[0].b;
        client_data[0].msg_size = sizeof(client_data[0]);

        std::cout << "Enter a2: ";
        std::cin >> client_data[1].a;
        std::cout << "Enter b2: ";
        std::cin >> client_data[1].b;
        client_data[1].msg_size = sizeof(client_data[1]);

        if (client_data[0].a == 0 && client_data[0].b == 0) {
            closesocket(sockfd);
            break;
        }

        int sent_bytes = send(sockfd, (const char*)client_data, sizeof(client_data), 0);
        if (sent_bytes == SOCKET_ERROR) {
            std::cerr << "Failed to send data. Error code: " << WSAGetLastError() << std::endl;
            closesocket(sockfd);
            WSACleanup();
            exit(1);
        }

        int recv_bytes = recv(sockfd, (char*)&result, sizeof(result_struct_t), 0);
        if (recv_bytes == SOCKET_ERROR) {
            std::cerr << "Failed to receive data. Error code: " << WSAGetLastError() << std::endl;
            closesocket(sockfd);
            WSACleanup();
            exit(1);
        }

        std::cout << "Result received = " << result.c << std::endl;
    }

    closesocket(sockfd);
    WSACleanup();
}

int main() {
    setup_tcp_communication();
    std::cout << "Application quits." << std::endl;
    return 0;
}
