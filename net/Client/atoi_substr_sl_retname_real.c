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

int		ft_atoisz(char *str)
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

char	*ft_sub_strsz(char *str, char end)
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

int		ft_slsz(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int		ft_return_namesz(char *argv)
{
	int i;
	int j;

	j = 0;
	i = 0;
	while (argv[i])
	{
		if (argv[i] == '/')
			j++;
		i++;
	}
	i = 0;
	while (j)
	{
		if (argv[i] == '/')
			j--;
		i++;
	}
	return (i);
}

void	ft_realsz(char **str, char *tmp)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new = malloc(sizeof(char) * (ft_slsz(*str) + ft_slsz(tmp)) + 2);
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
	new[i] = '\n';
	new[i + 1] = 0;
	free((*str));
	(*str) = new;
}
