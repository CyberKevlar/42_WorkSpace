#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>

typedef struct  client
{
    int     id;
    char    msg[500000];
}               t_client;

t_client    clients[1024];
int         max_fd = 0;
int         next_id = 0;
char        bufferRead[500000];
char        bufferWrite[500000];
fd_set      active;
fd_set      readyRead;
fd_set      readyWrite;

void exitError(char *str)
{
    if (str)
        write(2, str, strlen(str));
    exit(1);
}

void sendAll(int sender)
{
    for (int fd = 0; fd <= max_fd; fd++)
    {
        if (FD_ISSET(fd, &readyWrite) && (fd != sender))
            send(fd, bufferWrite, strlen(bufferWrite), 0);
    }
}

int main(int ac, char **av)
{
    if (ac != 2)
        exitError("Wrong number of arguments\n");

    int port = atoi(av[1]);
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    if (serverSocket < 0)
        exitError("Fatal error\n");

    bzero(clients, sizeof(clients));
    max_fd = serverSocket;
    FD_ZERO(&active);
    FD_SET(serverSocket, &active);

    struct sockaddr_in addr;
    socklen_t addr_len = sizeof(addr);
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = (1 << 24) + 127; // "127.0.0.1", in network order
    addr.sin_port = htons(port);

    if ((bind(serverSocket, (const struct sockaddr *)&addr, sizeof(addr))) < 0)
        exitError("Fatal error\n");
        
    if (listen(serverSocket, 128) < 0)
        exitError("Fatal error\n");

    while (1)
    {
        readyRead = readyWrite = active;
        if (select(max_fd + 1, &readyRead, &readyWrite, NULL, NULL) < 0)
            continue;

        for (int fd = 0; fd <= max_fd; fd++)
        {
            if (FD_ISSET(fd, &readyRead) && fd == serverSocket)
            {
                int clientSocket = accept(serverSocket, NULL, NULL);
                if (clientSocket < 0)
                    continue;
                max_fd = (clientSocket > max_fd) ? clientSocket : max_fd;
                clients[clientSocket].id = next_id++;
                FD_SET(clientSocket, &active);
                sprintf(bufferWrite, "server: client %d just arrived\n", clients[clientSocket].id);
                sendAll(clientSocket);
                break;
            }
            if (FD_ISSET(fd, &readyRead) && fd != serverSocket)
            {
                int read = recv(fd, bufferRead, 424242, 0);
                if (read <= 0)
                {
                    sprintf(bufferWrite, "server: client %d just left\n", clients[fd].id);
                    sendAll(fd);
                    FD_CLR(fd, &active);
                    close(fd);
                    break;
                }
                else
                {
                    for (int i = 0, j = strlen(clients[fd].msg); i < read; i++, j++)
                    {
                        clients[fd].msg[j] = bufferRead[i];
                        if (clients[fd].msg[j] == '\n')
                        {
                            clients[fd].msg[j] = '\0';
                            sprintf(bufferWrite, "client %d: %s\n", clients[fd].id, clients[fd].msg);
                            sendAll(fd);
                            bzero(&clients[fd].msg, strlen(clients[fd].msg));
                            j = -1;
                        }
                    }
                    break;
                }
            }
        }
    }
}