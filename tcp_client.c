/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tcp_client.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssong <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 15:45:14 by ssong             #+#    #+#             */
/*   Updated: 2018/03/02 18:14:05 by ssong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
// netinet contains a structure so we know the address we want to connect to

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

int main()
{
	int	 network_socket;

	// create a socket
	network_socket = socket(AF_INET, SOCK_STREAM, 0);

	// specify an address for the socket
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	// htons converts the port address to appropriate data format for struct
	server_address.sin_port = htons(9002);
	// sin_addr is a struct that holds data of the address we are trying to connect to
	// INADDR_ANY is same as connecting to 0.0.0.0
	server_address.sin_addr.s_addr = INADDR_ANY;
	// creates the connection between socket and server address
	int connect_status = connect(network_socket, (struct sockaddr *) &server_address, sizeof(server_address));
	// connect returns integer whether the connection occured
	if (connect_status == -1)
		ft_putstr("There was an error in connection to remote socket\n");

	// recieve data from the server
	char server_response[256];
	char my_message[256] = "ping";

	send(network_socket, my_message, sizeof(my_message), 0);
	recv(network_socket, &server_response, sizeof(server_response), 0);

	// print out the server's response
	ft_putstr(server_response);
	ft_putchar('\n');
	close(network_socket);
	return (0);
}
