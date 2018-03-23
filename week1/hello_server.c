//
//  hello_server.c
//  tipip
//
//  Created by 이광용 on 2018. 3. 16..
//  Copyright © 2018년 이광용. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
void error_handling(char *message);

int main(int argc, char *argv[])
{
    int serv_sock; //반환된 file descriptor. os 마다 별개의 file descriptor를 사용.
    int clnt_sock;
    
    struct sockaddr_in serv_addr; //주소에 대한 struct
    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_size; //_t : 16bit로 고정된 타입
    
    char message[]="hello world!";
    
    if(argc !=2)
    {
        printf("Usage : %s <port>\n",argv[0]);
        exit(1);
    }
    serv_sock=socket(PF_INET, SOCK_STREAM, 0); // socket 생성.
    //PH_INET: ipv4, SOCK_STREAM : connection oriented, 0 or IPPROTO_TCP
    if(serv_sock==-1)
        error_handling("socket() error");
    
    memset(&serv_addr, 0 , sizeof(serv_addr)); // 메모리 할당을 받음.
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_addr.s_addr=htonl(INADDR_ANY); // sin_addr : ip 주소 입력. 시스탬 내부적으로 처리
    serv_addr.sin_port=htons(atoi(argv[1])); // 사용자가 입력한 port 번호 할당
    
    if(bind(serv_sock,(struct sockaddr*) &serv_addr,sizeof(serv_addr))==-1) // socket ip 주소 할당
        error_handling("bind() error");
    
    if(listen(serv_sock, 5)==-1) // 5 : queue size. listen : 요청. SYN
        error_handling("listen() error");
    
    clnt_addr_size=sizeof(clnt_addr);
    clnt_sock=accept(serv_sock,(struct sockaddr*)&clnt_addr, &clnt_addr_size); // accept : 요청 수락. ACK
    if(clnt_sock==-1)
        error_handling("accept() error");
    
    write(clnt_sock, message, sizeof(message));
    close(clnt_sock);
    close(serv_sock);
    return 0;
}

void error_handling(char *message)
{
    fputs(message,stderr);
    fputc('\n', stderr);
    exit(1);
}
