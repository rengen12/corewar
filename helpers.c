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

void	parse_strtoint(void *var, void *str, int size)
{
	unsigned char	*s;
	int 			i;

	i = 0;
	s = (unsigned char *)str;
	*(unsigned int *)var = 0;
	while (size > 0)
	{
		*(unsigned int *)var += s[--size] << i;
		i += 8;
	}
}

void	parse_inttochar(void *var, void *str, int size)
{
	int 	v;

	v = *(short int *)var;
	((unsigned char *)str)[size - 1] = (unsigned char)((v << 24) >> 24);
	((unsigned char *)str)[size - 2] = (unsigned char)((v << 16) >> 24);
	((unsigned char *)str)[size - 3] = (unsigned char)((v << 8) >> 24);
	((unsigned char *)str)[size - 4] = (unsigned char)(v >> 24);
}

char	to_num(char val)
{
	if (val >= 0 && val <= 9)
		return (val + 48);
	return (0);
}
