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

#include "client.h"

int		ft_return_0(char **str)
{
	free(*str);
	return (0);
}

int		inner1sz(t_m *v, char **argv)
{
	memset(&v->hints, 0, sizeof(v->hints));
	v->hints.ai_family = AF_UNSPEC;
	v->hints.ai_socktype = SOCK_STREAM;
	v->ip_for_serv = ft_get_ipsz();
	if (!(v->ip_of_serv = ft_make_serv_ipsz(argv[2])))
		return (0);
	if ((v->fd = open(argv[1], O_RDONLY)) < 1)
		return (0);
	return (1);
}

void	inner2sz(t_m *v)
{
	ft_realsz(&v->res_str, v->ip_for_serv);
	v->status = getaddrinfo(v->ip_of_serv, "44445", &v->hints, &v->res);
	v->sockfd = socket(v->res->ai_family,
	v->res->ai_socktype, v->res->ai_protocol);
	connect(v->sockfd, v->res->ai_addr, v->res->ai_addrlen);
	send(v->sockfd, v->res_str, ft_slsz(v->res_str), 0);
	close(v->sockfd);
}

int		main(int argc, char *argv[])
{
	t_m v;

	if (!ft_check_argssz(argc, argv, &v.res_str))
		return (0);
	if (!inner1sz(&v, argv))
		return (0);
	while (get_next_line(v.fd, &v.tmp) > 0)
	{
		ft_realsz(&v.res_str, v.tmp);
		free(v.tmp);
	}
	inner2sz(&v);
	if (!(v.data = ft_recive_data_from_serversz(v.ip_for_serv)))
		return (0);
	v.files = ft_strsplitsz(v.data, '@');
	ft_execute_asm_and_startsz(v.files);
	return (0);
}
