/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tcp_server.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssong <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 16:34:34 by ssong             #+#    #+#             */
/*   Updated: 2018/03/03 09:43:23 by ssong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
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

int		ft_strcmp(const char *s1, const char *s2)
{
	int i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
	{
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int		main(void)
{
	int					server_socket;
	struct sockaddr_in	server_address;
	int					client_socket;
	char				client_message[256];

	server_socket = socket(AF_INET, SOCK_STREAM, 0);
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(9002);
	server_address.sin_addr.s_addr = INADDR_ANY;
	bind(server_socket, (struct sockaddr*)
			&server_address, sizeof(server_address));
	while (ft_strcmp(client_message, "ping"))
	{
		listen(server_socket, 42);
		client_socket = accept(server_socket, NULL, NULL);
		recv(client_socket, &client_message, sizeof(client_message), 0);
		if (ft_strcmp(client_message, "ping"))
			send(client_socket, "Send me ping", sizeof(client_message), 0);
	}
	send(client_socket, "Pong\nPong", sizeof(client_message), 0);
	close(server_socket);
	return (0);
}
