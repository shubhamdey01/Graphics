#include <stdio.h>
#include <sys/time.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include "unp.h"
#include "common.h"

struct {
    unsigned long add;
    unsigned short int port;
    int num;
    double data[5];
    double avg;
} clientData[3];

void init(int n, struct sockaddr_in x) {
    clientData[n].add = x.sin_addr.s_addr;
    clientData[n].port = x.sin_port;
    clientData[n].num = 0;
    clientData[n].avg = 0;
    for(int i=0; i<5; i++)
        clientData[n].data[i] = 0;
}


int main(int argc, char *argv[]) {
    MyMsg_t rxMsg1, rxMsg2;
    char *txMsg1 = "NEXT MSG", *txMsg2 = "STOP", msg[10];
    int sockfd, n=0, k;
    float sum=0;
    unsigned short cliPort;
    struct sockaddr_in servAddr, cliAddr; 
    char cli_ip_addr[16];
    socklen_t cliAddrLen;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    bzero(&servAddr, sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servAddr.sin_port = htons(atoi(argv[1]));

    if(bind(sockfd, (struct sockaddr *)&servAddr, sizeof(servAddr)) < 0) {
        if(errno == EADDRINUSE)
            printf("Bind error ... Port is still in use\n");
        else
            printf("Bind error ... \n");
        exit(0);
    }
    cliAddrLen = sizeof(cliAddr);
    bzero(cli_ip_addr, 16);

    rxMsg2.a.dElmt = atof(argv[2]);
    ConvertToNbw(&rxMsg2);

    while(1) {
        recvfrom(sockfd, &rxMsg1, sizeof(rxMsg1), 0, (struct sockaddr *)&cliAddr, &cliAddrLen);
        inet_ntop(AF_INET, &(cliAddr.sin_addr), &cli_ip_addr[0], 16); 
        printf("\nClient IP address : "); 
        puts(cli_ip_addr);
        cliPort = ntohs(cliAddr.sin_port);
        printf("Client port id : %u\n", cliPort);
        ConvertToHostByteOrder(&rxMsg1);
        if(rxMsg1.a.dElmt == 15.0) {
            if(n < 3) {
                init(n++, cliAddr);
                sendto(sockfd, &rxMsg2, sizeof(rxMsg2), 0, (struct sockaddr *)&cliAddr, cliAddrLen);
            }
            else {
                printf("Max client limit reached.\n");
                sendto(sockfd, txMsg2, sizeof(txMsg2), 0, (struct sockaddr *)&cliAddr, cliAddrLen);
            }
        }
        else {
            for(int i=0; i<n; i++) {
                if(clientData[i].add == cliAddr.sin_addr.s_addr && clientData[i].port == cliAddr.sin_port) {
                    k = (clientData[i].num++)%5;
                    clientData[i].data[k] = rxMsg1.a.dElmt;
                    sum = 0;
                    for(int j=0; j<5; j++)
                        sum += clientData[i].data[j];
                    clientData[i].avg = sum/5.0;
                    printf("avg = %g\n", clientData[i].avg);
                }
                else
                    continue;
                
                if(clientData[i].avg > 0.75*atof(argv[2])) {
                    printf("Average exceeds. Stopping the Client\n");
                    sendto(sockfd, txMsg2, sizeof(txMsg2), 0, (struct sockaddr *)&cliAddr, cliAddrLen);
                    break;
                }
                else {
                    sleep(1);
                    printf("\nAsking for next message\n");
                    sendto(sockfd, txMsg1, sizeof(txMsg1), 0, (struct sockaddr *)&cliAddr, cliAddrLen); 
                }
            }
        }        
    }
    close(sockfd);
}
