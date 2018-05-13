/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssong <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/12 20:43:17 by ssong             #+#    #+#             */
/*   Updated: 2018/05/12 21:03:09 by ssong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "proxy.h"

void	error(char *msg)
{
	perror(msg);
	exit(0);
}

int		error_check(t_parse *http_info)
{
	if (http_info == NULL)
		return (1);
	else if (strcmp(http_info->method, "GET"))
		return (2);
	else if (strncmp(http_info->url, "http://", 7))
		return (3);
	else if (strncmp(http_info->version, "HTTP/1.0", 8))
		return (4);
	return (0);
}

int		str_digit(char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

void	send_to_client(t_client *client, t_host *host)
{
	send(client->client_socket, host->server_response,
		sizeof(host->server_response), 0);
	close(client->client_socket);
}
