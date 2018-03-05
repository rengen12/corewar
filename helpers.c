/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amichak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 16:10:00 by amichak           #+#    #+#             */
/*   Updated: 2018/03/05 16:10:00 by amichak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	parse_int(void *var, void *str4)
{
	unsigned char	*str;

	str = (unsigned char *)str4;
	*(unsigned int *)var = str[3];
	*(unsigned int *)var += str[2] << 8;
	*(unsigned int *)var += str[1] << 16;
	*(unsigned int *)var += str[0] << 24;
}

char	to_num(char val)
{
	if (val >= 0 && val <= 9)
		return (val + 48);
	return (0);
}
