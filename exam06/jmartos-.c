#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>

typedef struct s_client
{
    int id;
    char msg[370000];
} t_client;

t_client clients[2048];
fd_set setCurrent;
fd_set setRead;
fd_set setWrite;
int maxFd = 0;
int nextId = 0;
char bufferRead[400000];
char bufferWrite[400000];

void exitError(char *str)
{
    write(2, str, strlen(str));
    write(2, "\n", 1);
    exit(1);
}

void sendAll(int sender)
{
    for (int fd = 0; fd <= maxFd; fd++)
    {
        if (FD_ISSET(fd, &setWrite) && (fd != sender))
        {
            if (send(fd, bufferWrite, strlen(bufferWrite), 0) == -1)
            {
                FD_CLR(fd, &setCurrent);
                close(fd);
            }
        }
    }
}

int main(int ac, char **av)
{
    if (ac != 2)
        exitError("Wrong number of arguments");

    struct sockaddr_in address;
    socklen_t len = sizeof(struct sockaddr);
    int serverFd = socket(AF_INET, SOCK_STREAM, 0);

    if (serverFd == -1)
        exitError("Fatal error");

    maxFd = serverFd;

    FD_ZERO(&setCurrent);
    FD_SET(serverFd, &setCurrent);

    bzero(clients, sizeof(clients));
    bzero(&address, sizeof(address));

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    address.sin_port = htons(atoi(av[1]));

    if (bind(serverFd, (const struct sockaddr *)&address, sizeof(address)) == -1)
        exitError("Fatal error");

    if (listen(serverFd, 100) == -1)
        exitError("Fatal error");

    while (1)
    {
        setRead = setWrite = setCurrent;

        if (select(maxFd + 1, &setRead, &setWrite, 0, 0) == -1)
            continue;

        for (int fd = 0; fd <= maxFd; fd++)
        {
            if (FD_ISSET(fd, &setRead))
            {
                if (fd == serverFd)
                {
                    int clientFd = accept(fd, (struct sockaddr *)&address, &len);
                    if (clientFd == -1)
                        continue;
                    if (clientFd > maxFd)
                        maxFd = clientFd;
                    clients[clientFd].id = nextId++;
                    FD_SET(clientFd, &setCurrent);
                    sprintf(bufferWrite, "server: client %d just arrived\n", clients[clientFd].id);
                    sendAll(clientFd);
                    break;
                }
                else
                {
                    int readBytes = recv(fd, bufferRead, sizeof(bufferRead), 0);
                    if (readBytes <= 0)
                    {
                        sprintf(bufferWrite, "server: client %d just left\n", clients[fd].id);
                        sendAll(fd);
                        FD_CLR(fd, &setCurrent);
                        bzero(clients[fd].msg, strlen(clients[fd].msg));
                        close(fd);
                        break;
                    }
                    else
                    {
                        for (int i = 0, j = strlen(clients[fd].msg); i < readBytes; i++, j++)
                        {
                            clients[fd].msg[j] = bufferRead[i];
                            if (clients[fd].msg[j] == '\n')
                            {
                                clients[fd].msg[j] = '\0';
                                sprintf(bufferWrite, "client %d: %s\n", clients[fd].id, clients[fd].msg);
                                sendAll(fd);
                                bzero(clients[fd].msg, strlen(clients[fd].msg));
                                j = -1;
                            }
                        }
                    }
                }
            }
        }
    }
    return 0;
}