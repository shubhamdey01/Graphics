#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/select.h>
#include "unp.h"
#include "common.h"


int sockfd, to_exit = 0, i, select_no;
float v;
socklen_t servAddrLen;
struct sockaddr_in cliAddr, servAddr;

int main(int argc, char **argv) {
    MyMsg_t txMsg;
    unsigned char txbuff[80];
    char rxMsg[10];
    int i, j, select_no, servAddrLen;
    fd_set readfd;

    if(argc < 3) {
        printf("Usage : <myclient> <server IP address> <server port>\n");
        exit(0);
    }

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if(sockfd < 0) {
        switch(errno) {
            case EACCES:
            printf("Permission to create socket of the specified type is denied\n");
            break; 

            case EAFNOSUPPORT:
            printf("Socket of given address family not supported\n");
            break;

            case EINVAL:
            printf("Invalid values in type\n");
            break;

            default:
            printf("Other socket errors\n");
            break;
        }
        exit(0);
    }

    bzero(&servAddr, sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    inet_pton(AF_INET, argv[1], &servAddr.sin_addr);
    servAddr.sin_port = htons(atoi(argv[2]));

    txMsg.a.dElmt = 15.0;
    ConvertToNbw(&txMsg);
    sendto(sockfd, &txMsg, sizeof(txMsg),0,(struct sockaddr *)&servAddr, sizeof(servAddr));
    recvfrom(sockfd, &txMsg, sizeof(txMsg), 0, (struct sockaddr *)&servAddr, &servAddrLen);
    printf("\nSever->client : ");
    v = ConvertToHostByteOrder(&txMsg);

    srand48(time(0));

    while(1) { 
        txMsg.a.dElmt = (double)(-v+2*v*drand48());
        printf("%g\n", txMsg.a.dElmt);

        ConvertToNbw(&txMsg);  

        sendto(sockfd, &txMsg, sizeof(txMsg),0,(struct sockaddr *)&servAddr, sizeof(servAddr));

        bzero(rxMsg, 10);
        recvfrom(sockfd, &rxMsg, 10, 0, (struct sockaddr *)&servAddr, &servAddrLen);
        if(strcmp(rxMsg,"STOP")) {
            sleep(2);
            printf("\nSever->client : ");
            fputs(rxMsg, stdout);
            printf("\n");
        }
        else {
            printf("\nSever->client : ");
            fputs(rxMsg, stdout);
            printf("\n");
            printf("Terminated from server\n");
            break;
        }
    }
    close(sockfd);
}
