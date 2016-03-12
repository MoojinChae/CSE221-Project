#define _GNU_SOURCE
#include <fcntl.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>

int calculate_size(char* size_in_str, char* unit);
int calculate_size(char* size_in_str, char* unit) {
    const int kb = 1024;
    const int mb = 1024 * 1024;
    const int gb = 1024 * 1024 * 1024;

    int size = atoi(size_in_str);

    if (!strcmp(unit, "K"))
        return size * kb;

    if (!strcmp(unit, "M"))
        return size * mb;

    if (!strcmp(unit, "G"))
        return size * gb;

    return size;
}

int main(int argc, char* argv[])
{
    int listen_fd, comm_fd, clilen;
    int pid;
 
    struct sockaddr_in servaddr, cliaddr;

    int size = calculate_size(argv[1], argv[2]);
    char filename[80];
    snprintf(filename, sizeof (filename), "./random%s%s", argv[1], argv[2]);
    printf("filename: %s size: %d\n", filename, size);
 
    listen_fd = socket(AF_INET, SOCK_STREAM, 0);
 
    bzero(&servaddr, sizeof(servaddr));
 
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htons(INADDR_ANY);
    servaddr.sin_port = htons(atoi(argv[3]));
 
    bind(listen_fd, (struct sockaddr *) &servaddr, sizeof(servaddr));
 
    listen(listen_fd, 10);
    clilen = sizeof(cliaddr);
 
    while (1) {
        comm_fd = accept(listen_fd, (struct sockaddr*) &cliaddr, &clilen);

        if (comm_fd < 0) {
            perror("Error: accept()");
            exit(1);
        }

        pid = fork();

        if (pid == 0) {
            close(listen_fd);

            char buf[100];
            // open up a file.
            int fd;
            static char block[4096] __attribute__ ((__aligned__ (4096)));
            const int block_size = 4096;

            int bytes_read = 0;
            int block_bytes_read = 0;
            int total_bytes_read = 0;

            int bytes_write = 0;
            int block_bytes_write = 0;
            int total_bytes_write = 0;

            
            if ((fd = open(filename, O_RDONLY | O_DIRECT)) == -1) {
                perror("Error: read error");
                exit(1);
            }

            if (lseek(fd, 0, SEEK_SET) == -1) {
                perror("Error: lseek()");
                exit(1);
            }

            while (total_bytes_write < size) {
                // waiting for request
                read(comm_fd, buf, 100);

                // read a block of file then write to the socket
                block_bytes_read = 0;
                while (block_bytes_read < 4096) {
                    if ((bytes_read = read(fd, block, block_size - block_bytes_read)) == -1) {
                         perror("Error: read()");
                    }
                    block_bytes_read += bytes_read;
                    total_bytes_read += bytes_read;
                }

                block_bytes_write = 0;
                while (block_bytes_write < 4096) {
                    if ((bytes_write = write(comm_fd, block, block_size - block_bytes_write)) == -1) {
                        perror("Error: write()");
                    }
                    block_bytes_write += bytes_write;
                    total_bytes_write += bytes_write;
                }

            }

            printf("Block written to socket total:%d\n", total_bytes_write);
            close(comm_fd);
            exit(0);
        } else {
            close(comm_fd);
        }
    }

    return 0;
}

