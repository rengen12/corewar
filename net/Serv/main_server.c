/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szverhov <szverhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 18:54:24 by szverhov          #+#    #+#             */
/*   Updated: 2017/10/30 12:15:13 by szverhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	ft_inner1_sz(t_m *v)
{
	v->files = (char**)malloc(sizeof(char*) * (v->count_players + 1));
	memset(&v->hints, 0, sizeof(v->hints));
	memset(&v->buff, 0, sizeof(v->buff));
	v->hints.ai_family = AF_UNSPEC;
	v->hints.ai_socktype = SOCK_STREAM;
	v->my_ip = ft_get_ip_sz();
	getaddrinfo(v->my_ip, "44445", &v->hints, &v->res);
	v->sockfd = socket(v->res->ai_family,
	v->res->ai_socktype, v->res->ai_protocol);
	v->clients_ip = (char**)malloc(sizeof(char*) * 5);
	v->i = 0;
}

void	ft_inner2_sz(t_m *v)
{
	bind(v->sockfd, v->res->ai_addr, v->res->ai_addrlen);
	listen(v->sockfd, BACKLOG);
	FD_ZERO(&v->set);
	FD_SET(v->sockfd, &v->set);
	v->timeout.tv_sec = 10;
	v->timeout.tv_usec = 0;
	v->rv = select(v->sockfd + 1, &v->set, 0, 0, &v->timeout);
}

int		ft_inner3_sz(t_m *v)
{
	if (v->rv == 0)
		return (0);
	else
	{
		v->addr_size = sizeof(v->their_addr);
		v->new_fd = accept(v->sockfd,
		(struct sockaddr *)&v->their_addr, &v->addr_size);
	}
	recv(v->new_fd, v->buff, 100000, 0);
	v->files[v->i] = ft_sub_str_sz(v->buff, 0);
	memset(&v->buff, 0, sizeof(v->buff));
	v->clients_ip[v->i] = ft_get_client_ip_sz(v->files, v->i);
	v->i++;
	return (1);
}

void	ft_inner4_sz(t_m *v)
{
	close(v->sockfd);
	v->clients_ip[v->i] = 0;
	v->files[v->i] = 0;
	if (v->clients_ip[0] == 0)
		return ;
	ft_send_data_to_clients_sz(v->files, v->clients_ip);
	ft_execute_asm_and_start_sz(v->files);
}

int		main(int argc, char *argv[])
{
	t_m v;

	if (!ft_check_args_sz(argc, argv, &v.count_players))
		return (0);
	ft_inner1_sz(&v);
	while (v.count_players--)
	{
		ft_inner2_sz(&v);
		if (!ft_inner3_sz(&v))
			break ;
	}
	ft_inner4_sz(&v);
	return (0);
}
