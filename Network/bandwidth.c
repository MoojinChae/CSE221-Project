#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <math.h>
#include <sys/time.h>
#include "cpu.h"

#define SEND_COUNT 100
#define MSGSIZE 50*1048576

void error(const char *msg) {
    perror(msg);
    exit(1);
}

void measure_bandwidth(float overhead, char* ip) {
    unsigned t;
    float t_float, avg, stddev, min, max;
    int sk;
    struct sockaddr_in server_addr;
    struct hostent *server;
    static char buffer[MSGSIZE]; //4Mbytes

    server = gethostbyname(ip);

    bzero((char *) &server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(5001);
    bcopy((char *)server->h_addr, (char *)&server_addr.sin_addr.s_addr, server->h_length);

    for (int i = 0; i < MSGSIZE-1; i++)
        buffer[i] = 'a';

    int wn;
    avg = 0.0;
    stddev = 0.0;
    min = 10000000.0;
    max = 0.0;
    static struct timeval tm1;
    static struct timeval tm2;
    printf("Responding...\n");
    for(int i = 1; i <= SEND_COUNT ; i++) {
        sk = socket(AF_INET, SOCK_STREAM, 0);
        if (sk < 0) error("ERROR opening socket");

        if (connect(sk,(struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) {
            error("ERROR connecting");
        }

        gettimeofday(&tm1, NULL);
        
        int total_sent = 0;
        while (total_sent < MSGSIZE) {
            wn = write(sk, buffer, MSGSIZE);
            if (wn == -1) error("ERROR writing to socket");
            else total_sent += wn;
        }
        gettimeofday(&tm2, NULL);

        t_float = ((tm2.tv_sec-tm1.tv_sec)*1000000 + tm2.tv_usec-tm1.tv_usec)/1000.0;

        printf("[%d] Total Bytes Sent = %d and time = %fms\n", i, total_sent, t_float);
        float prev_avg = avg;
        avg += (t_float - prev_avg) / i;
        stddev += (t_float- prev_avg) * (t_float - avg);
        if (t_float > max) max = t_float;
        if (t_float < min) min = t_float;

        close(sk);
    }
    stddev = sqrt(stddev / (SEND_COUNT - 1));
    printf("[%s] average = %fms, std = %f, min = %fms, max = %fms\n", ip, avg, stddev, min, max);

}

int main(int argc, char* argv[]) {
	measure_bandwidth(8, "192.168.0.9");
    measure_bandwidth(8, "localhost");
    return 0;
}