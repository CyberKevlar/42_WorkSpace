#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>

int extract_message(char **buf, char **msg)
{
	char	*newbuf;
	int	i;

	*msg = 0;
	if (*buf == 0)
		return (0);
	i = 0;
	while ((*buf)[i])
	{
		if ((*buf)[i] == '\n')
		{
			newbuf = calloc(1, sizeof(*newbuf) * (strlen(*buf + i + 1) + 1));
			if (newbuf == 0)
				return (-1);
			strcpy(newbuf, *buf + i + 1);
			*msg = *buf;
			(*msg)[i + 1] = 0;
			*buf = newbuf;
			return (1);
		}
		i++;
	}
	return (0);
}

char *str_join(char *buf, char *add)
{
	char	*newbuf;
	int		len;

	if (buf == 0)
		len = 0;
	else
		len = strlen(buf);
	newbuf = malloc(sizeof(*newbuf) * (len + strlen(add) + 1));
	if (newbuf == 0)
		return (0);
	newbuf[0] = 0;
	if (buf != 0)
		strcat(newbuf, buf);
	free(buf);
	strcat(newbuf, add);
	return (newbuf);
}


int main() {
	int sockfd, connfd, len;
	struct sockaddr_in servaddr, cli; 

	// socket create and verification 
	sockfd = socket(AF_INET, SOCK_STREAM, 0); 
	if (sockfd == -1) { 
		printf("socket creation failed...\n"); 
		exit(0); 
	} 
	else
		printf("Socket successfully created..\n"); 
	bzero(&servaddr, sizeof(servaddr)); 

	// assign IP, PORT 
	servaddr.sin_family = AF_INET; 
	servaddr.sin_addr.s_addr = htonl(2130706433); //127.0.0.1
	servaddr.sin_port = htons(8081); 
  
	// Binding newly created socket to given IP and verification 
	if ((bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr))) != 0) { 
		printf("socket bind failed...\n"); 
		exit(0); 
	} 
	else
		printf("Socket successfully binded..\n");
	if (listen(sockfd, 10) != 0) {
		printf("cannot listen\n"); 
		exit(0); 
	}
	len = sizeof(cli);
	connfd = accept(sockfd, (struct sockaddr *)&cli, &len);
	if (connfd < 0) { 
        printf("server acccept failed...\n"); 
        exit(0); 
    } 
    else
        printf("server acccept the client...\n");
}

//////////////////////////////////////////////
// PRUEBA V.1 DE EXAMEN MADE IN YO MISMO!!! //
//////////////////////////////////////////////

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>

typedef struct  s_client
{
    int     id;
    char    msg[180000];
}               t_client;

t_client    clients[2048];
int         maxFd = 0;
int         nextId = 0;
char        bufferRead[200000];
char        bufferWrite[200000];
fd_set      current;
fd_set      readyRead;
fd_set      readyWrite;

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
        if (FD_ISSET(fd, &readyWrite) && (fd != sender))
            send(fd, bufferWrite, strlen(bufferWrite), 0);
    }
}

int main(int ac, char **av)
{
    if (ac != 2)
        exitError("Wrong number of arguments");

    int serverFd = socket(AF_INET, SOCK_STREAM, 0);
    if (serverFd < 0)
        exitError("Fatal error");

    maxFd = serverFd;
    bzero(clients, sizeof(clients));
    FD_ZERO(&current);
    FD_SET(serverFd, &current);

    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    address.sin_port = htons(atoi(av[1]));

    if (bind(serverFd, (const struct sockaddr *)&address, sizeof(address)) < 0)
        exitError("Fatal error");

    if (listen(serverFd, 128) < 0)
        exitError("Fatal error");

    while (1)
    {
        readyRead = readyWrite = current;

        if (select(maxFd + 1, &readyRead, &readyWrite, NULL, NULL) < 0)
            continue;

        for (int fd = 0; fd <= maxFd; fd++)
        {
            if (FD_ISSET(fd, &readyRead) && fd == serverFd)
            {
                int clientFd = accept(serverFd, NULL, NULL);
                if (clientFd < 0)
                    continue;
                if (clientFd > maxFd)
                    maxFd = clientFd;
                clients[clientFd].id = nextId++;
                FD_SET(clientFd, &current);
                sprintf(bufferWrite, "server: client %d just arrived\n", clients[clientFd].id);
                sendAll(clientFd);
                break;
            }
            else if (FD_ISSET(fd, &readyRead) && fd != serverFd)
            {
                int readBytes = recv(fd, bufferRead, sizeof(bufferRead), 0);
                if (readBytes <= 0)
                {
                    sprintf(bufferWrite, "server: client %d just left\n", clients[fd].id);
                    sendAll(fd);
                    FD_CLR(fd, &current);
                    close(fd);
                    bzero(clients[fd].msg, sizeof(clients[fd].msg));
                    break;
                }
                else
                {
                    bufferRead[readBytes] = '\0'; // Asegura terminación null
                    for (int i = 0; i < readBytes; i++)
                    {
                        int len = strlen(clients[fd].msg);
                        if (len < sizeof(clients[fd].msg) - 1)
                            clients[fd].msg[len] = bufferRead[i];
                        clients[fd].msg[len + 1] = '\0';

                        if (bufferRead[i] == '\n')
                        {
                            sprintf(bufferWrite, "client %d: %s", clients[fd].id, clients[fd].msg);
                            sendAll(fd);
                            bzero(clients[fd].msg, sizeof(clients[fd].msg));
                        }
                    }
                }
            }
        }
    }
    return 0;
}