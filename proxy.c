/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proxy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssong <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/12 10:10:00 by ssong             #+#    #+#             */
/*   Updated: 2018/05/12 20:45:30 by ssong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "proxy.h"

/*
**	Set up listening on the chosen port.
*/

t_client	*initialize_socket(t_client *listen, int port)
{
	listen = malloc(sizeof(t_client));
	listen->server_socket = socket(AF_INET, SOCK_STREAM, 0);
	listen->server_address.sin_family = AF_INET;
	listen->server_address.sin_port = htons(port);
	listen->server_address.sin_addr.s_addr = INADDR_ANY;
	bind(listen->server_socket, (struct sockaddr*)
		&listen->server_address, sizeof(listen->server_address));
	return (listen);
}

t_parse		*parse_message(t_client *client, t_parse *http_info)
{
	char	**buffer;

	if (ft_countwords(client->client_message, ' ') != 3)
	{
		send(client->client_socket,
			"incorrect number of arguments\n", 30, 0);
		return (http_info);
	}
	http_info = malloc(sizeof(t_parse));
	buffer = ft_strsplit(client->client_message, ' ');
	http_info->method = buffer[0];
	http_info->url = buffer[1];
	http_info->version = buffer[2];
	sprintf(http_info->final, "GET %s HTTP/1.0\r\n\r\n", http_info->url);
	return (http_info);
}

t_parse		*read_send(t_client *client, t_parse *http_info)
{
	listen(client->server_socket, 42);
	client->client_socket = accept(client->server_socket, NULL, NULL);
	while (error_check(http_info))
	{
		recv(client->client_socket,
			&client->client_message, sizeof(client->client_message), 0);
		http_info = parse_message(client, http_info);
	}
	return (http_info);
}

t_host		*initialize_host(t_host *host, t_parse *info)
{
	host = malloc(sizeof(t_host));
	info->url = ft_strchr(info->url, '/') + 2;
	printf("%s\n", info->url);
	if (!(info->IP = gethostbyname(info->url)))
		error("no such host");
	host->network_socket = socket(AF_INET, SOCK_STREAM, 0);
	host->server_address.sin_family = AF_INET;
	host->server_address.sin_port = htons(80);
	ft_memcpy(&host->server_address.sin_addr.
		s_addr, info->IP->h_addr, info->IP->h_length);
	host->connect_status = connect(host->network_socket, (struct sockaddr*)&
		host->server_address, sizeof(struct sockaddr));
	if (host->connect_status == -1)
		error("error connecting to host\n");
	printf("Connected to %s\n", info->url);
	printf("%s\n", info->final);
	send(host->network_socket, info->final,
		ft_strlen(info->final), 0);
	recv(host->network_socket, &host->server_response,
		sizeof(host->server_response), 0);
	return (host);
}

int			main(int argc, char **argv)
{
	t_client		*socket;
	t_host			*host;
	t_parse			*http_info;
	int				port;

	if (argc != 2)
		error("usage: ./proxy <port>\n");
	if (!str_digit(argv[1]))
		error("usage: ./proxy <port>\n\tnumber only for port\n");
	port = atoi(argv[1]);
	if (port < 1024 || port > 65535)
		error("set port above 1024 and below 65535\n");
	socket = NULL;
	http_info = NULL;
	host = NULL;
	socket = initialize_socket(socket, port);
	http_info = read_send(socket, http_info);
	host = initialize_host(host, http_info);
	send_to_client(socket, host);
	return (0);
}
