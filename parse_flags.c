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

static int	handle_dump(int ac, char **av, int *i, t_flags *fl)
{
	if (++(*i) < ac && ft_is_alldigits(av[*i]) && ft_is_pint(ft_atoi(av[*i])))
		fl->dump = (int)ft_atoi(av[*i]);
	else
		return (ft_puterrendl("Error: wrong parameter in argument"));
	return (0);
}

static int handle_n(int ac, char **av, int *i, t_flags *fl)
{
	if (++(*i) < ac && ft_is_alldigits(av[*i]) && ft_is_pshint(ft_atoi(av[*i])))
		fl->n++;
	else
		return (ft_puterrendl("Error: wrong parameter in argument"));
	return (0);
}

int		parse_flags(t_flags *fl, int ac, char **av)
{
	int	i;

	i = 0;
	*fl = (t_flags){0, -1, 0, 0, 0, 0, 0, 1, CYCLE_TO_DIE, 0};
	while (++i < ac)
		if (!ft_strcmp("-v", av[i]))
			fl->v = 1;
		else if (!ft_strcmp("-l", av[i]))
			fl->l = 1;
		else if (!ft_strcmp("-a", av[i]))
			fl->a = 1;
		else if (!ft_strcmp("-dump", av[i]) && handle_dump(ac, av, &i, fl))
			return (1);
		else if (!ft_strcmp("-n", av[i]) && handle_n(ac, av, &i, fl))
			return (1);
		else
			fl->nplayers++;
	if (fl->nplayers > 0 && fl->nplayers <= MAX_PLAYERS)
		fl->mem_for_champ = MEM_SIZE / fl->nplayers;
	else
		return(ft_puterrendl("Error: wrong number of champion(s)"));
	return (0);
}
