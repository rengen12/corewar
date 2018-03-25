/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_alldigits.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amichak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 14:08:33 by amichak           #+#    #+#             */
/*   Updated: 2017/12/28 17:36:30 by amichak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int		ft_is_alldigits(char *str)
{
	if (str && *str && ft_isdigit(*str))
	{
		while (*str && !ft_issptab(*str))
			if (!ft_isdigit(*str++))
				return (0);
	}
	else
		return (0);
	return (1);
}
