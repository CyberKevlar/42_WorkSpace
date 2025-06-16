while(1)
{
	fdread = fdwrite = fdactives;

	if (select(fdmax + 1, &fdread, &fdwrite, 0, 0) == -1)
		continue ;

	for (int fdclient = 0; fdclient <= fdmax; fdclient++)
	{
		if (FD_ISSET(fdclient, &fdread))
		{
			if (fdclient == fdserver)
			{
				//nueva conexion...
				int fdnew = accept(fdclient, (struct sockaddr *)&servaddr, &len);
				if (fdnew == -1)
					continue ;
				if(fdnew > fdmax)
					fdmax = fdnew;
				clients[fdnew].id = nextid++;
				FD_SET(fdnew, &fdactives);
				sprintf(bufferwrite, "el cliente %d se conecto\n", clients[fdnew].id);
				sendall(fdnew);
				break ;
			}
			else
			{
				int bytes = recv(fdclient, bufferread, sizeof(bufferread), 0);
        			if (bytes <= 0)
				{
					//desconexion...
					sprintf(bufferwrite, "el cliente %d se desconecto\n", clients[fdclient].id);
					sendall(fdclient)
					bzero(clients[fdclient].msg, strlen(clients[fdclient].msg))
					FD_CLR(fdclient, &fdactives);
					close(fdclient);
					break ;
				}
				else
				{
					//enviar mensaje...
					for (int i = 0, j = strlen(clients[fdclient].msg); i < bytes; i++, j++)
					{
						
					}
				}
			}
		}
	}
}
return (0);
