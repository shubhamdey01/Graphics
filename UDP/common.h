#ifndef _COMMON_H
#define _COMMON_H

typedef struct
{
  union mydata{
    double dElmt;
    unsigned int iElmt;
  } a;
} MyMsg_t;

#endif

void ConvertToNbw(MyMsg_t *msg) {
    unsigned int tmp;
    tmp = htonl(msg->a.iElmt);
    msg->a.iElmt = tmp;
}

float ConvertToHostByteOrder(MyMsg_t *msg) {
    msg->a.iElmt = ntohl(msg->a.iElmt);
    printf("%g\n", msg->a.dElmt);
    return msg->a.dElmt;
}