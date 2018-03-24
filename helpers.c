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

int		pr_usage(void)
{
	ft_printf("./corewar [-v | -a | -dump nbr_cycles {0 .. 2147483647}] [[-n "
					  "{1 .. 4294967295} number] champion1.cor] ...\n\t-a - "
					  "reveal hidden aff commands\n\t-v - visualisation\n\t"
					  "-dump - memory dump on nbr_cycles cycle");
	return (1);
}

void	set_last_pl(t_player *pls)
{
	if (pls)
	{
		while (pls->next)
			pls = pls->next;
		pls->is_last = 1;
	}
}
