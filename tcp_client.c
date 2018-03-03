/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tcp_client.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssong <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 15:45:14 by ssong             #+#    #+#             */
/*   Updated: 2018/03/03 09:24:23 by ssong            ###   ########.fr       */
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

int		main(int argc, char **argv)
{
	int					network_socket;
	struct sockaddr_in	server_address;
	int					connect_status;
	char				server_response[256];

	if (argc != 2)
	{
		ft_putstr("usage: message to client\n");
		return (0);
	}
	network_socket = socket(AF_INET, SOCK_STREAM, 0);
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(9002);
	server_address.sin_addr.s_addr = INADDR_ANY;
	connect_status = connect(network_socket, (struct sockaddr *)
			&server_address, sizeof(server_address));
	if (connect_status == -1)
		ft_putstr("There was an error in connection to remote socket\n");
	send(network_socket, argv[1], sizeof(argv[1]), 0);
	recv(network_socket, &server_response, sizeof(server_response), 0);
	ft_putstr(server_response);
	ft_putchar('\n');
	close(network_socket);
	return (0);
}
