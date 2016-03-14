#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

#define BUF_SIZE 34
#define SEND_COUNT 100

void error(const char *msg) {
    perror(msg);
    exit(1);
}


void measure_round_trip() {
    int sk, new_sk, port;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len;
    char buffer[BUF_SIZE];
    char message[BUF_SIZE];
    for (int i = 0; i < BUF_SIZE; i++)
        message[i] = 'a';

    sk = socket(AF_INET, SOCK_STREAM, 0);
    if (sk < 0) error("ERROR opening socket");

    bzero((char *) &server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(5374);

    if (bind(sk, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) {
        error("ERROR on binding");
    }
    
    listen(sk, 5);

    client_len = sizeof(client_addr);
    
    printf("Starting!\n");
    int cnt = 0, rn, wn;
    for(int i = 1; i <= SEND_COUNT ; i++) {
        new_sk = accept(sk, (struct sockaddr *) &client_addr, &client_len);
        if (new_sk < 0) error("ERROR on accept");
        else printf("sucess!");

        while(1) {
            rn = read(new_sk, buffer, BUF_SIZE); 
            if (rn <= 0) error("ERROR reading from socket");
            if (rn != BUF_SIZE) printf("Unsuccess receive! %d bytes\n", rn);
            else if (rn == BUF_SIZE) {
                printf("Client finished sending\n");
                wn = write(new_sk, message, BUF_SIZE);
                if (wn < 0) error("ERROR writing to socket");
                else break;
            }
        }

        close(new_sk);
    }
    close(sk);
}

int main(int argc, char *argv[]) {
    measure_round_trip();
    return 0; 
}