/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proxy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssong <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/12 10:10:00 by ssong             #+#    #+#             */
/*   Updated: 2018/05/12 16:16:38 by ssong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h> /* struct hostent, gethostbyname */
#include <netinet/in.h>

/*
** A web proxy is a program that reads a request 
** from a browser, forwards that request to a web
** server, reads the reply from the web server, and
** forwards the reply back to the browser. People
** typically use web proxies to cache pages for better
** performance, to modify web pages in transit
** (e.g. to remove annoying advertisements), or for weak anonymity.
*/

/* Usually HTTP a client communicated directly with a server
** but with a proxy. The Proxy opens a connection to the server
** , and passes on the client's requests. The proxy recieves the 
** reply from the server, and then sends that reply back to the
** client. 
** Notice that the proxy acts as a server to the client
** 	and as a client to the server.
*/

/*
** Why use a proxy? There are a few possible reasons:
**
** Performance: By saving a copy of the pages that it fetches, 
**	a proxy can reduce the need to create connections to remote 
**	servers. This can reduce the overall delay involved in 
**	retrieving a page, particularly if a server is remote or 
**	under heavy load.
** 
** Content Filtering and Transformation: While in the simplest 
**	case the proxy merely fetches a resource without inspecting it
**	, there is nothing that says that a proxy is limited to blindly
** 	fetching and serving files. The proxy can inspect the requested
**	URL and selectively block access to certain domains, reformat web
**	pages (for instances, by stripping out images to make a page 
**	easier to display on a handheld or other limited-resource client)
**	, or perform other transformations and filtering.
**
** Privacy: Normally, web servers log all incoming requests for resources.
**	This information typically includes at least the IP address of the client,
**	the browser or other client program that they are using 
**	(called the User-Agent), the date and time, and the requested file.
**	If a client does not wish to have this personally identifiable
**	information recorded, routing HTTP requests through a proxy is one
**	solution. All requests coming from clients using the same proxy
**	appear to come from the IP address and User-Agent of the proxy itself,
**	rather than the individual clients. If a number of clients use the
**	same proxy (say, an entire business or university), it becomes much
**	harder to link a particular HTTP transaction to a single computer or
**	individual.
*/

typedef	struct	s_parse
{
	char *method;
	char *url;
	char *version;
	char *final;
}		t_parse;

typedef	struct	s_host
{
	int			network_socket;
	struct sockaddr_in	server_address;
	int			connect_status;
	char			server_response[10000];
}

typedef struct	s_client
{
	int			server_socket;
	struct sockaddr_in	server_address;
}		t_client;

t_client	*initialize_client(t_client *client, int port)
{
	client->server_socket = socket(AF_INET, SOCK_STREAM, 0);
	client->server_address.sin_family = AF_INET;
	client->server_address.sin_port = htons(port);
	client->server_address.sin_addr.s_addr = INADDR_ANY;
	bind(client->server_socket, (struct sockaddr*)
		&client->server_address, sizeof(client->server_address));
	return (client);
}

t_host			initialize_host(t_host *host)
{
i	host = malloc(sizeof(t_host));
	host->network_socket = socket(AF_INET, SOCK_STREAM, 0);
	host->server_address.sin_family = AF_INET;
	host->server_address.sin_port = htons(80);
	host->server_address.sn_addr.s_addr = INADDR_ANY;
	connect_status = connect(network_socket, (struct sockaddr *)
			&server_address, sizeof(server_address));
	if (connect_status == -1)
		error("error connecting to host");
}

int	error_check(t_parse *http_info)
{
	if ((strcmp(http_info->method, "GET"))
		return (-1);
	else if (strncmp(http_info->url, "http://", 7))
		return (-1);
	else if (strcmp(http_info->version, "HTTP/1.0"))
		return (-1);
	return (0);
}

t_parse	*parse_message(char *client_message)
{
	t_parse	*http_info;
	char 	**buffer;

	http_info = malloc(sizeof(t_parse));
	if (ft_countwords(client_message, ' ') != 3)
	{
		printf("incorrect number or arguments\n");
		return (-1);
	}
	buffer = ft_strsplit(client_message, ' ');
	http_info->method = buffer[0];
	http_info->url = buffer[1];
	http_info->version = buffer[2];
	return (http_info);
}

void	error(char *msg)
{
	perror(msg);
	exit(0);
}

void				read_send(t_client *client)
{
	char		client_message[256];
	char 		*host = "www.google.com";
	char		temp[50];
	t_parse		*http_info;

	while (1)
	{
		listen(server_socket, 42);
		client_socket = accept(server_socket, NULL, NULL);
		recv(client_socket, &client_message, sizeof(client_message), 0);
		http_info = parse_message(client_message);
		server = gethostbyname(host);
		if (server == NULL)
			error("ERROR, no such host");
		
		if (!check_error(http_info))
		{
			http_info->url = ft_strchr(http_info->url, '/') + 2;
			sprintf(http_info->final, "GET %s HTTP/1.0\r\n", http_info->url);
			if (send(
		}
		else
			send(client_socket, "400 : BAD REQUEST\nONLY HTTP/1.0", 55,0);
		close(client_socket);
	}
}

int	str_digit(char *str)
{
	while (*str)
	{
		if (!isdigit(*str))
			return (0);
		str++;	
	}
	return (1);
}


int					main(int argc, char **argv)
{
	t_client		*client;
	int			port;
	t_host			*host;


	if (argc != 2)
	{
		printf("usage: ./proxy <port>\n");
		return (0);
	}
	if (!str_digit(argv[1]))
	{
		printf("usage: ./proxy <port>\n\tnumber only for port\n");
		return (0);
	}
	port = atoi(argv[1]);
	if (port < 1024 || port > 65535)
	{
		printf("set port above 1024 and below 65535\n");
		return (0);
	}
	client = initialize_client(client, port);
	host = initialize_host(host);
	read_send(client);
	return (0);
}
