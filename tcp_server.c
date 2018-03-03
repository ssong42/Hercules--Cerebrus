/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tcp_server.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssong <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 16:34:34 by ssong             #+#    #+#             */
/*   Updated: 2018/03/03 12:54:53 by ssong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

struct sockaddr_in	initialize_server(int *server_socket)
{
	struct sockaddr_in	server_address;

	*server_socket = socket(AF_INET, SOCK_STREAM, 0);
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(9002);
	server_address.sin_addr.s_addr = INADDR_ANY;
	bind(*server_socket, (struct sockaddr*)
			&server_address, sizeof(server_address));
	return (server_address);
}

void				read_send(int server_socket)
{
	char	client_message[256];
	int		client_socket;

	while (ft_strcmp(client_message, "ping"))
	{
		listen(server_socket, 42);
		client_socket = accept(server_socket, NULL, NULL);
		recv(client_socket, &client_message, sizeof(client_message), 0);
		if (ft_strcmp(client_message, "ping"))
			send(client_socket, "Send me ping", sizeof(client_message), 0);
	}
	send(client_socket, "Pong\nPong", sizeof(client_message), 0);
}

int					main(int argc, char **argv)
{
	int					server_socket;
	struct sockaddr_in	server_address;

	if (argc > 2)
	{
		ft_putstr("only one argument\n");
		return (0);
	}
	else if (argc == 2 && ft_strcmp(argv[1], "-D"))
	{
		ft_putstr("usage:\n\toptional: [-D] Daemon\n");
		return (0);
	}
	server_address = initialize_server(&server_socket);
	read_send(server_socket);
	close(server_socket);
	return (0);
}
