#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

#define SEND_COUNT 100
#define MSGSIZE 50*1048576

void error(const char *msg) {
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[]) {
	int sk, new_sk, port;
    socklen_t client_len;
    static char buffer[MSGSIZE];
    struct sockaddr_in server_addr, client_addr;

    sk = socket(AF_INET, SOCK_STREAM, 0);
    if (sk < 0) error("ERROR opening socket");

    bzero((char *) &server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(5001);

    if (bind(sk, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) {
        error("ERROR on binding");
    }

    listen(sk, 5);
    client_len = sizeof(client_addr);
    printf("Starting!\n");
    int rn;
    for(int i = 1; i <= SEND_COUNT ; i++) {
    	new_sk = accept(sk, (struct sockaddr *) &client_addr, &client_len);
        if (new_sk < 0) error("ERROR on accept");

        printf("[%d] Client connected!\n", i);
        int total_received = 0;
        while (total_received < MSGSIZE) {
            rn = read(new_sk, buffer, MSGSIZE);
            if (rn == -1) error("ERROR reading from socket");
            else if (rn == 0) {
                printf("Client finished sending\n");
                break;
            }
            else {
                total_received += rn;
                printf("Received %d\n", total_received);
            }
        }
        close(new_sk);
    }

    close(sk);
    return 0;
}