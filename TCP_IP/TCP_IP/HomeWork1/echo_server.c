#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1024
void error_handling(char *message);

int main(int argc, char *argv[]) {
    int serv_sock, clnt_sock;
    char message[BUF_SIZE];
    int str_len, i;
    
    int port_Number = atoi(argv[1]); //convert char * to int
    struct sockaddr_in serv_adr, clnt_adr;
    socklen_t clnt_adr_sz;
    
    if(argc != 2) {
        printf("Usage : %s <port>\n", argv[0]);
        exit(1);
    }
    
    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    //create socket. socket method return file descriptor. PF_INET : IPv4, SOCK_STREAM : Connection Oriented(TCP), 0 : TCP (Need to replace 'IPROTO_TCP')
    if(serv_sock == -1) {
        error_handling("socket() error");
    }
    
    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_port = htons(port_Number);
    serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
    //Network : Big-Endian, Host : Little-Endian. So need to convert Little-Endian to Big-Endian using htons method
    //port : htons, ip address : htonl
    if(bind(serv_sock, (struct sockaddr *)&serv_adr, sizeof(serv_adr)) == -1) {
        error_handling("bind() error");
    }
    
    if(listen(serv_sock, 5) == -1) { //listen(socket file descriptor, queue size)
        error_handling("listen() error");
    }
    
    clnt_adr_sz = sizeof(clnt_adr);
    
    for(i=0; i<5; i++) {
        clnt_sock = accept(serv_sock, (struct sockaddr *)&clnt_adr, &clnt_adr_sz);
        if(clnt_sock == -1) {
            error_handling("accept() error");
        }
        else {
            printf("Connected client %d \n", i+1);
            printf("Clinet %d's IP address :  %s\n", i+1, inet_ntoa(clnt_adr.sin_addr));
            //clnt_adr.sin_addr : int. inet_ntoa : convert int to char * (123 -> 127.0.0.1)
            printf("Clinet %d's port number :  %d\n", i+1, ntohs(clnt_adr.sin_port) );
            //clnt_adr.sin_port is using little-Endian need to convert to big-endian
        }
        
        while((str_len = read(clnt_sock, message, BUF_SIZE)) != 0) {
            write(clnt_sock, message, str_len);
        }
        
        close(clnt_sock);
    }
    
    close(serv_sock);
    return 0;
}

void error_handling(char *message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}

