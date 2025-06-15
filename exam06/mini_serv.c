#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>

typedef struct s_client
{
    int id;
    char msg[370000];
} t_client;

t_client clients[2048];
fd_set fd_actives;
fd_set fd_read;
fd_set fd_write;
int fd_max = 0;
int next_id = 0;
char buffer_read[400000];
char buffer_write[400000];

void exit_error(char *str)
{
    write(2, str, strlen(str));
    write(2, "\n", 1);
    exit(1);
}

void send_to_all(int fd_sender)
{
    for (int fd_client = 0; fd_client <= fd_max; fd_client++)
    {
        if (FD_ISSET(fd_client, &fd_write) && (fd_client != fd_sender))
            send(fd_client, buffer_write, strlen(buffer_write), 0);
    }
}

int main(int ac, char **av)
{
    if (ac != 2)
        exit_error("Wrong number of arguments");

    struct sockaddr_in server_address;
    socklen_t len = sizeof(struct sockaddr);
    int fd_server = socket(AF_INET, SOCK_STREAM, 0);

    if (fd_server == -1)
        exit_error("Fatal error");

    fd_max = fd_server;

    FD_ZERO(&fd_actives);
    FD_SET(fd_server, &fd_actives);

    bzero(clients, sizeof(clients));
    bzero(&server_address, sizeof(server_address));

    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htonl(2130706433);
    server_address.sin_port = htons(atoi(av[1]));

    if (bind(fd_server, (const struct sockaddr *)&server_address, sizeof(server_address)) == -1)
        exit_error("Fatal error");

    if (listen(fd_server, 100) == -1)
        exit_error("Fatal error");

    while (1)
    {
        fd_read = fd_write = fd_actives;

        if (select(fd_max + 1, &fd_read, &fd_write, 0, 0) == -1) // ASI SABEMOS SI ALGUIEN TIENE ALGO PARA LEER O ESCRIBIR
            continue ;

        for (int fd_client = 0; fd_client <= fd_max; fd_client++) // RECORRE TODOS LOS CLIENTES, INCLUYENDO EL SERVIDOR.
        {
            if (FD_ISSET(fd_client, &fd_read)) // ¿HAY ALGUN CLIENTE TIENE ALGO LEIDO?
            {
                if (fd_client == fd_server) // SI FD_CLIENT LLEGA A FD_SERVER ES PORQUE UN CLIENTE QUIERE CONECTARSE.
                {
                    int fd_new = accept(fd_client, (struct sockaddr *)&server_address, &len);
                    if (fd_new == -1)
                        continue;
                    if (fd_new > fd_max)
                        fd_max = fd_new;
                    clients[fd_new].id = next_id++;
                    FD_SET(fd_new, &fd_actives);
                    sprintf(buffer_write, "server: client %d just arrived\n", clients[fd_new].id);
                    send_to_all(fd_new);
                    break ;
                }
                else // SI EL CLIENTE ES UN CLIENTE QUE YA EXISTE COMPROBAMOS SU MENSAJE POR SI TIENE ALGO O NO.
                {
                    int bytes = recv(fd_client, buffer_read, sizeof(buffer_read), 0); // COMPROBAMOS QUE TAN LARGO ES EL MENSAJE.
                    if (bytes <= 0) // SI NO HAY NADA QUE LEER ES QUE UN CLIENTE VA A DESCONECTARSE.
                    {
                        sprintf(buffer_write, "server: client %d just left\n", clients[fd_client].id);
                        send_to_all(fd_client);
                        FD_CLR(fd_client, &fd_actives);
                        bzero(clients[fd_client].msg, strlen(clients[fd_client].msg));
                        close(fd_client);
                        break ;
                    }
                    else // SI HAY ALGO QUE LEER, LO PROCESAMOS Y LO ENVIAMOS A TODOS LOS CLIENTES.
                    {
                        for (int i = 0, j = strlen(clients[fd_client].msg); i < bytes; i++, j++)
                        {
                            clients[fd_client].msg[j] = buffer_read[i];
                            if (clients[fd_client].msg[j] == '\n')
                            {
                                clients[fd_client].msg[j] = '\0';
                                sprintf(buffer_write, "client %d: %s\n", clients[fd_client].id, clients[fd_client].msg);
                                send_to_all(fd_client);
                                bzero(clients[fd_client].msg, strlen(clients[fd_client].msg));
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