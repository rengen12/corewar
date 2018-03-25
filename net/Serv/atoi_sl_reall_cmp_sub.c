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

int		ft_atoi_sz(char *str)
{
	int					minus;
	unsigned long int	result;

	minus = 1;
	result = 0;
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	if (*str == '-')
		minus = -1;
	if (*str == '+' || *str == '-')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		if ((result > 922337203685477580 || (result == 922337203685477580
		&& (*str - '0') > 7)) && minus == 1)
			return (-1);
		if ((result > 922337203685477580 || (result == 922337203685477580
		&& (*str - '0') > 8)) && minus == -1)
			return (0);
		result = result * 10 + (*str - 48);
		str++;
	}
	return ((int)(result * minus));
}

int		ft_sl_sz(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_reall_sz(char **str, char *tmp)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new = malloc(sizeof(char) * (ft_sl_sz(*str) + ft_sl_sz(tmp)) + 2);
	while ((*str)[i])
	{
		new[i] = (*str)[i];
		i++;
	}
	while (tmp[j])
	{
		new[i] = tmp[j];
		i++;
		j++;
	}
	new[i] = 0;
	free((*str));
	(*str) = new;
}

int		ft_strcmp_sz(const char *s1, const char *s2)
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

char	*ft_sub_str_sz(char *str, char end)
{
	int		i;
	char	*tmp;

	i = 0;
	while (str[i] != end && str[i] != '\0')
		i++;
	if (str[i] == '\0' && end != '\0')
		return (0);
	if (!(tmp = (char*)malloc(sizeof(char) * i + 3)))
		return (0);
	i = -1;
	while (str[++i] != end)
		tmp[i] = str[i];
	tmp[i] = 0;
	return (tmp);
}
