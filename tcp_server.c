/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tcp_server.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssong <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 16:34:34 by ssong             #+#    #+#             */
/*   Updated: 2018/03/02 18:12:55 by ssong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *str)
{
	while (*str)
	{
		ft_putchar(*str);
		str++;
	}
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
	{
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int main()
{
	char server_message[256] = "Pong\nPong";
	char error_message[256] = "NOT PING";
	// create server socket
	int server_socket;
	server_socket = socket(AF_INET, SOCK_STREAM, 0);

	// define the server address
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	
	// htons converts the port address to appropriate data format for struct
	server_address.sin_port = htons(9002);
	
	// sin_addr is a struct that holds data of the address we are trying to connect to
	// INADDR_ANY is the ip address of local machine
	server_address.sin_addr.s_addr = INADDR_ANY;

	// bind the socket to our specified IP and port
	bind(server_socket, (struct sockaddr*) &server_address, sizeof(server_address));

	listen(server_socket, 42);

	int	client_socket;
	// second parament of accept can store the information of the client into a struct (PORT, IP);
	client_socket = accept(server_socket, NULL, NULL);

	char client_message[256];
	char test[6] = "ping";

	recv(client_socket, &client_message, sizeof(client_message), 0);
	ft_putstr(client_message);
	ft_putchar('\n');
	if (ft_strcmp(client_message, test) == 0)
	{
		// send the message
		send(client_socket, server_message, sizeof(server_message), 0);
	}
	else
		send(client_socket, error_message, sizeof(error_message), 0);
	close(server_socket);
	return (0);
}
