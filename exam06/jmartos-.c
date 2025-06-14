#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>

typedef struct  s_client
{
    int         id;
    char        msg[370000];
}               t_client;

t_client    clients[2048];
fd_set      set_current;
fd_set      set_read;
fd_set      set_write;
int         max_fd = 0;
int         next_id = 0;
char        buffer_read[400000];
char        buffer_write[400000];

void exitError(char *str)
{
    write(2, str, strlen(str));
    write(2, "\n", 1);
    exit(1);
}

void sendAll(int sender)
{
    for (int fd = 0; fd <= max_fd; fd++)
    {
        if (FD_ISSET(fd, &set_write) && (fd != sender))
        {
            if (send(fd, buffer_write, strlen(buffer_write), 0) == -1)
            {
                FD_CLR(fd, &set_current);
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
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (server_fd == -1)
        exitError("Fatal error");

    max_fd = server_fd;

    FD_ZERO(&set_current);
    FD_SET(server_fd, &set_current);

    bzero(clients, sizeof(clients));
    bzero(&address, sizeof(address));

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    address.sin_port = htons(atoi(av[1]));

    if (bind(server_fd, (const struct sockaddr *)&address, sizeof(address)) == -1)
        exitError("Fatal error");

    if (listen(server_fd, 100) == -1)
        exitError("Fatal error");

    while (1)
    {
        set_read = set_write = set_current;

        if (select(max_fd + 1, &set_read, &set_write, 0, 0) == -1)
            continue;

        for (int fd = 0; fd <= max_fd; fd++)
        {
            if (FD_ISSET(fd, &set_read))
            {
                if (fd == server_fd)
                {
                    int client_fd = accept(fd, (struct sockaddr *)&address, &len);
                    if (client_fd == -1)
                        continue;
                    if (client_fd > max_fd)
                        max_fd = client_fd;
                    clients[client_fd].id = next_id++;
                    FD_SET(client_fd, &set_current);
                    sprintf(buffer_write, "server: client %d just arrived\n", clients[client_fd].id);
                    sendAll(client_fd);
                    break;
                }
                else
                {
                    int read_bytes = recv(fd, buffer_read, sizeof(buffer_read), 0);
                    if (read_bytes <= 0)
                    {
                        sprintf(buffer_write, "server: client %d just left\n", clients[fd].id);
                        sendAll(fd);
                        FD_CLR(fd, &set_current);
                        bzero(clients[fd].msg, strlen(clients[fd].msg));
                        close(fd);
                        break;
                    }
                    else
                    {
                        for (int i = 0, j = strlen(clients[fd].msg); i < read_bytes; i++, j++)
                        {
                            clients[fd].msg[j] = buffer_read[i];
                            if (clients[fd].msg[j] == '\n')
                            {
                                clients[fd].msg[j] = '\0';
                                sprintf(buffer_write, "client %d: %s\n", clients[fd].id, clients[fd].msg);
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