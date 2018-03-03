# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ssong <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/03/03 10:33:59 by ssong             #+#    #+#              #
#    Updated: 2018/03/03 10:35:34 by ssong            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

all:
	gcc -Wall -Werror -Wextra tcp_server.c libft.a -o tcp_server
	gcc -Wall -Werror -Wextra tcp_client.c libft.a -o tcp_client

clean:
	rm -f tcp_server
	rm -f tcp_client
