#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <unistd.h>

int main() {

    int sock;
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("creating stream socket");
        exit(2);
    }

    struct sockaddr_in {
        short sin_family;
        unsigned short sin_port;
        struct in_addr sin_addr;
        char sin_zero[8];
    };

    struct in_addr {
        unsigned long s_addr;
    };

    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(5678);

    int bi = bind(sock, (struct sockaddr *) &server, sizeof(server));
    if (bi < 0) {
        printf("konnte nicht gebunden werden");
        exit(-1);
    }

    struct sockaddr_in client;
    int filedescriptor;
    socklen_t client_len;
    char in[1024];
    int bytes_read;

    int ls = listen(sock, 5);
    if (ls < 0) {
        printf("konnte nicht gesetzt werden");
        exit(-1);
    }

    while (1) {
        filedescriptor = accept(sock, (struct sockaddr *) &client, &client_len);
        bytes_read = read(filedescriptor, in, 1024);

        while (bytes_read > 0) {
            write(filedescriptor, in, bytes_read);
            bytes_read = read(filedescriptor, in, 1024);
        }

        close(filedescriptor);

    }
    close(sock);
}
