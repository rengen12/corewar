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

char	*ft_get_ipsz(void)
{
	size_t	q;
	char	*who_am_i;
	int		i;
	char	*res;

	i = 0;
	q = 20;
	who_am_i = malloc(20);
	gethostname(who_am_i, q);
	while (who_am_i[i] && who_am_i[i] != '.')
		i++;
	who_am_i[i] = 0;
	res = ft_make_serv_ipsz(who_am_i);
	free(who_am_i);
	return (res);
}

void	inner_rdfssz(t_rdfs *v, char *my_ip)
{
	v->buff = malloc(100000);
	memset(&v->hints, 0, sizeof(v->hints));
	v->hints.ai_family = AF_UNSPEC;
	v->hints.ai_socktype = SOCK_STREAM;
	getaddrinfo(my_ip, "44442", &v->hints, &v->res);
	v->sockfd = socket(v->res->ai_family,
	v->res->ai_socktype, v->res->ai_protocol);
	bind(v->sockfd, v->res->ai_addr, v->res->ai_addrlen);
	listen(v->sockfd, 3);
	FD_ZERO(&v->set);
	FD_SET(v->sockfd, &v->set);
	v->timeout.tv_sec = 60;
	v->timeout.tv_usec = 0;
	v->rv = select(v->sockfd + 1, &v->set, 0, 0, &v->timeout);
}

char	*ft_recive_data_from_serversz(char *my_ip)
{
	t_rdfs	v;

	inner_rdfssz(&v, my_ip);
	if (v.rv == 0)
	{
		free(v.res->ai_addr);
		free(v.res);
		return (0);
	}
	else
	{
		v.addr_size = sizeof(v.their_addr);
		v.new_fd = accept(v.sockfd,
		(struct sockaddr *)&v.their_addr, &v.addr_size);
	}
	recv(v.new_fd, v.buff, 100000, 0);
	close(v.sockfd);
	free(v.res->ai_addr);
	free(v.res);
	return (v.buff);
}

char	*ft_strsubbsz(char *s, unsigned int start, size_t len)
{
	char			*res;
	unsigned int	i;
	unsigned int	end;

	if (s == NULL)
		return (NULL);
	res = (char*)malloc(sizeof(char) * len + 1);
	if (res == NULL)
		return (NULL);
	i = 0;
	end = start + len;
	while (start < end)
	{
		res[i] = s[start];
		i++;
		start++;
	}
	res[i] = 0;
	return (res);
}

int		count_of_wordssz(char *s, char c)
{
	size_t i;
	size_t w_count;

	if (s == 0)
		return (0);
	w_count = 0;
	i = 0;
	if (s[0] != c)
		w_count++;
	while (s[i])
	{
		if ((s[i] == c && s[i + 1] != c && s[i + 1] != 0))
			w_count++;
		i++;
	}
	return (w_count);
}
