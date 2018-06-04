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
#define LISTENQ 10
#define MAXLINE 80
typedef struct sockaddr SA; 

void sig_child(int);
void str_echo(int);

int 
main(int argc, char const *argv[])
{
    int listen_fd, conn_fd;
    pid_t child_pid;
    socklen_t client_scoket_len;
    struct sockaddr_in client_addr, server_addr;
    //when protocol is 0, if the type is stream, which means tcp; if the type is datagram, means udp  
    listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(SERVER_PORT);
    if (bind(listen_fd, (SA *)&server_addr, sizeof(server_addr)) == -1)
        return 0;
    listen(listen_fd, LISTENQ);
    signal(SIGCHLD, sig_child);
    for( ; ; )
    {
        client_scoket_len = sizeof(client_addr);
        if( (conn_fd = accept(listen_fd, (SA *)&client_addr, &client_scoket_len)) < 0)
        {
            if (errno == EINTR)
                continue;
            else
                printf("accept error\n");
        }
        if( (child_pid = fork()) == 0)
        {
            close(listen_fd);
            str_echo(conn_fd);
            exit(0);
        }
        close(conn_fd);
    }
    return 0;
}

void sig_child(int signo)
{
    pid_t pid;
    int stat;
    while( (pid = waitpid(-1, &stat, WNOHANG)) > 0)
        printf("child %d terminated\n", pid);
    return;
}

void 
str_echo(int socket_fd)
{
    ssize_t n;
    char buff[MAXLINE];
again:
    while ( (n = read(socket_fd, buff, MAXLINE)) > 0)
    {
        printf("receive %s", buff);
        write(socket_fd, buff, n);
        bzero(buff, sizeof(buff));
    }
    if (n < 0 && errno == EINTR)
    {
        goto again;
    }
    else if(n<0)
    {
        printf("str_echo: read error");
        exit(0);
    }
}
