/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proxy.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssong <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/12 20:42:25 by ssong             #+#    #+#             */
/*   Updated: 2018/05/12 20:58:27 by ssong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROXY_H
# define PROXY_H
# include "libft.h"
# include <string.h>
# include <stdarg.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <arpa/inet.h>
# include <sys/socket.h>
# include <netdb.h>
# include <netinet/in.h>

typedef	struct	s_parse
{
	char			*method;
	char			*url;
	char			*version;
	char			finale[5000];
	struct hostent	*ip;
}				t_parse;

typedef	struct	s_host
{
	int					network_socket;
	struct sockaddr_in	server_address;
	int					connect_status;
	char				server_response[10000];
}				t_host;

typedef struct	s_client
{
	int					server_socket;
	int					client_socket;
	struct sockaddr_in	server_address;
	int					connect_status;
	char				client_message[5000];
}				t_client;

void			error(char *msg);
int				error_check(t_parse *http_info);
int				str_digit(char *str);
void			send_to_client(t_client *client, t_host *host);
#endif
