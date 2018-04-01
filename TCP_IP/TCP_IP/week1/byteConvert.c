//
//  byteConvert.cpp
//  
//
//  Created by 이광용 on 2018. 3. 23..
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main(int argc, char *argv[]) {
    unsigned short host_port = 0x1234;
    unsigned short net_port;
    unsigned long host_addr = 0x12345678;
    unsigned long net_addr;
    //Host : Little Endian
    //Network : Big Endian
    net_port = htons(host_port);
    net_addr = htonl(host_addr);
    
    printf("%x\n", host_port);
    printf("%x\n",net_port);
    printf("%lx\n",host_addr);
    printf("%lx\n",net_addr);
    
}
