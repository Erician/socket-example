#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <errno.h>
#include <signal.h>
#include <sys/wait.h>

uint16_t SERVER_PORT = 2000;
#define MAXLINE 80
typedef struct sockaddr SA; 

void str_cli(FILE *fp, int socket_fd);

int 
main(int argc, char const *argv[])
{
    int socket_fd;
    struct sockaddr_in server_addr;
    if( argc != 2)
    {
        printf("usage: tcpcli <IPAddress>\n");
        return 0;
    }   
    
    socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    inet_pton(AF_INET, argv[1], &server_addr.sin_addr);
    if (connect(socket_fd, (SA *)&server_addr, sizeof(server_addr)) < 0)
        return 0;
    str_cli(stdin, socket_fd);
    exit(0);
}

void str_cli(FILE *fp, int socket_fd)
{
    
    char send_line[MAXLINE], receive_line[MAXLINE];
    while(fgets(send_line, MAXLINE, fp) != NULL)
    {
        write(socket_fd, send_line, strlen(send_line));
        int n;
        if ((n = read(socket_fd, receive_line, MAXLINE)) < 0)
        {
            printf("str_cli: server terminated prematurely");
            exit(0);
        }
        fputs(receive_line, stdout);
        bzero(send_line, sizeof(send_line));
        bzero(receive_line, sizeof(receive_line));
    }
}
