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

void	ft_add_num_sz(char *ip, char **res, int *adds)
{
	char	*new_res;
	int		i;
	int		j;

	i = -1;
	j = 0;
	new_res = malloc(30);
	while ((*res)[++i])
		new_res[i] = (*res)[i];
	while (ip && ip[j] >= '0' && ip[j] <= '9')
	{
		if (j == 0 && ip[j] == '0')
			(*adds) = -2;
		new_res[i] = ip[j];
		i++;
		j++;
	}
	new_res[i] = '.';
	new_res[i + 1] = 0;
	free((*res));
	(*res) = new_res;
	(*adds)++;
}

char	*ft_make_serv_ip_sz(char *ip)
{
	char	*res;
	int		i;
	int		num;
	int		adds;

	res = ft_sub_str_sz("10.11", 0);
	i = 0;
	adds = 0;
	while (ip[i])
	{
		if (i == 0 && ip[i] != 'e')
			return (ft_free_return_zero(&res));
		if (i == 0 && (num = ft_atoi_sz(ip + 1) <= 3) && num > 0)
			ft_add_num_sz(ip + 1, &res, &adds);
		if (ip[i] == 'r' && (num = ft_atoi_sz(ip + i + 1) <= 12) && num > 0)
			ft_add_num_sz(ip + i + 1, &res, &adds);
		if (ip[i] == 'p' && (num = ft_atoi_sz(ip + i + 1) <= 18) && num > 0)
			ft_add_num_sz(ip + i + 1, &res, &adds);
		i++;
	}
	if (adds != 3)
		return (ft_free_return_zero(&res));
	res[ft_sl_sz(res) - 1] = 0;
	return (res);
}

char	*ft_get_ip_sz(void)
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
	res = ft_make_serv_ip_sz(who_am_i);
	free(who_am_i);
	return (res);
}

char	*ft_get_client_ip_sz(char **files, int num_file)
{
	char	*tmp;
	int		i;
	char	*res;

	tmp = files[num_file];
	i = 0;
	while (tmp[i])
		i++;
	i--;
	while (tmp[i - 1] != '\n')
		i--;
	res = ft_sub_str_sz(tmp + i, 0);
	res[ft_sl_sz(res) - 1] = 0;
	tmp[i] = 0;
	return (res);
}

int		ft_allready_send_sz(char **clients_ip, int *i)
{
	int j;

	j = 0;
	if ((*i) == 0)
		return (1);
	while (clients_ip[j])
	{
		if (j == (*i))
		{
			j++;
			continue ;
		}
		if (ft_strcmp_sz(clients_ip[(*i)], clients_ip[j]) == 0)
		{
			(*i)++;
			return (0);
		}
		j++;
	}
	return (1);
}
