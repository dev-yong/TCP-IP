#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

void error_handling(char *message);
int main(int argc, char *argv[]) {
    int sock;
    struct sockaddr_in serv_addr;
    char message[30];
    int str_len;
    
    char *ip_Address = argv[1];
    int port_Num = atoi(argv[2]);
    
    if(argc!=3) {
        printf("Usage : %s <IP> <port> \n", argv[0]);
        exit(1);
    }
    
    sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock == -1) { error_handling("socket() error"); }
    
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(ip_Address);
    serv_addr.sin_port = htons(port_Num);
    
    if (connect(sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr) == -1)) {
        error_handling("connect() error!");
    }
    
    str_len = read(sock, message, sizeof(message) - 1);
    
    if (str_len == -1) { error_handling("read() error!"); }
    
    printf("Message from server : %s\n", message);
    close(sock);
    return 0;
}

void error_handling(char *message)
{
    fputs(message,stderr);
    fputc('\n', stderr);
    exit(1);
}
