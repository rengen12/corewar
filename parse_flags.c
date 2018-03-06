/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amichak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 16:09:00 by amichak           #+#    #+#             */
/*   Updated: 2018/03/05 16:09:00 by amichak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		parse_flags(t_flags *fl, int ac, char **av)
{
	int	i;

	i = 0;
	*fl = (t_flags){0, 0, 0, 0, 0};
	while (++i < ac)
		if (!ft_strcmp("-v", av[i]))
			fl->v = 1;
		else if (!ft_strcmp("-dump", av[i]))
		{
			if (++i < ac && ft_is_alldigits(av[i]) && ft_is_pint(ft_atoi(av[i])))
				fl->dump = (int)ft_atoi(av[i]);
			else
				return (ft_puterrendl("Error: wrong parameter in argument"));
		}
		else if (!ft_strcmp("-n", av[i]))
		{
			if (++i < ac && ft_is_alldigits(av[i]) && ft_is_pshint(ft_atoi(av[i])))
				fl->n++;
			else
				return (ft_puterrendl("Error: wrong parameter in argument"));
		}
		else
			fl->nplayers++;
	fl->mem_for_champ = fl->nplayers > 0 ? MEM_SIZE / fl->nplayers : 0;
	return (0);
}
