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

int		ft_strcmpsz(const char *s1, const char *s2)
{
	while ((unsigned char)*s1 != 0 || (unsigned char)*s2 != 0)
	{
		if ((unsigned char)*s1 - (unsigned char)*s2 != 0)
			return ((unsigned char)*s1 - (unsigned char)*s2);
		s1++;
		s2++;
	}
	return (0);
}

int		ft_check_name(char *name)
{
	int i;
	int dot;

	i = 0;
	dot = 0;
	while (name[i])
	{
		if (name[i] == '.')
			dot = 1;
		i++;
	}
	if (dot == 0)
		return (0);
	else
		while (name[i] != '.')
			i--;
	if (ft_strcmpsz(name + i, ".s\n") == 0)
		return (1);
	else
		return (0);
}

void	ft_add_numsz(char *ip, char **res, int *adds)
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

char	*ft_free_return_zerosz(char **str)
{
	free(*str);
	return (0);
}

char	*ft_make_serv_ipsz(char *ip)
{
	char	*res;
	int		i;
	int		num;
	int		adds;

	res = ft_sub_strsz("10.11", 0);
	i = 0;
	adds = 0;
	while (ip[i])
	{
		if (i == 0 && ip[i] != 'e')
			return (ft_free_return_zerosz(&res));
		if (i == 0 && (num = ft_atoisz(ip + 1) <= 3) && num > 0)
			ft_add_numsz(ip + 1, &res, &adds);
		if (ip[i] == 'r' && (num = ft_atoisz(ip + i + 1) <= 12) && num > 0)
			ft_add_numsz(ip + i + 1, &res, &adds);
		if (ip[i] == 'p' && ip[i + 1] != 0 &&
		(num = ft_atoisz(ip + i + 1) <= 18) && num > 0)
			ft_add_numsz(ip + i + 1, &res, &adds);
		i++;
	}
	if (adds != 3)
		return (ft_free_return_zerosz(&res));
	res[ft_slsz(res) - 1] = 0;
	return (res);
}
