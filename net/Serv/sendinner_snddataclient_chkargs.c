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

void	ft_send_inner_sz(t_sdtc *v, char **clients_ip)
{
	memset(&v->hints, 0, sizeof(v->hints));
	v->hints.ai_family = AF_UNSPEC;
	v->hints.ai_socktype = SOCK_STREAM;
	if ((v->status = getaddrinfo(clients_ip[v->i],
	"44442", &v->hints, &v->res)) < 0)
		return ;
	if ((v->sockfd = socket(v->res->ai_family,
	v->res->ai_socktype, v->res->ai_protocol)) < 0)
		return ;
	if ((connect(v->sockfd, v->res->ai_addr, v->res->ai_addrlen)) < 0)
	{
		close(v->sockfd);
		return ;
	}
	if ((send(v->sockfd, v->res_str, ft_sl_sz(v->res_str), 0)) < 0)
	{
		close(v->sockfd);
		return ;
	}
	close(v->sockfd);
}

void	ft_send_data_to_clients_sz(char **files, char **clients_ip)
{
	t_sdtc v;

	v.res_str = malloc(sizeof(char));
	v.res_str[0] = 0;
	v.i = 0;
	while (files[v.i])
	{
		ft_reall_sz(&v.res_str, files[v.i]);
		ft_reall_sz(&v.res_str, "@");
		v.i++;
	}
	v.i = -1;
	while (clients_ip[++v.i])
	{
		if (clients_ip[v.i][0] == 'a')
		{
			v.i++;
			continue ;
		}
		ft_send_inner_sz(&v, clients_ip);
		clients_ip[v.i][0] = 'a';
		free(v.res->ai_addr);
		free(v.res);
	}
	free(v.res_str);
}

int		ft_check_args_sz(int argc, char **argv, int *count_players)
{
	if (argc != 2)
		return (0);
	(*count_players) = ft_atoi_sz(argv[1]);
	if ((*count_players) < 1 || (*count_players) > 4)
		return (0);
	return (1);
}

char	*ft_free_return_zero(char **str)
{
	free(*str);
	return (0);
}

void	ft_rm_rf_cors(char **names)
{
	int		i;
	char	*rm_rf;

	i = 0;
	while (names[i])
	{
		rm_rf = ft_sub_str_sz("rm -rf ", 0);
		ft_reall_sz(&rm_rf, names[i]);
		system(rm_rf);
		free(rm_rf);
		i++;
	}
	i = -1;
	while (names[++i])
		free(names[i]);
}
