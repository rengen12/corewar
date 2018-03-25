/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amichak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 16:09:00 by amichak           #+#    #+#             */
/*   Updated: 2018/03/24 22:14:01 by amichak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int	handle_dump(int ac, char **av, int *i, t_flags *fl)
{
	ssize_t	num;

	if (!fl->v)
	{
		if (++(*i) < ac)
		{
			if (ft_is_alldigits(av[*i]))
			{
				num = ft_atoi(av[*i]);
				if (num > 0 && ft_is_pint(num))
				{
					fl->dump = (int)num;
					return (0);
				}
			}
		}
		return (ft_puterrendl("Error: wrong argument"));
	}
	else
		(*i)++;
	return (0);
}

static int	handle_n(int ac, char **av, int *i, t_flags *fl)
{
	ssize_t	num;

	if (++(*i) < ac)
	{
		if (ft_is_alldigits(av[*i]))
		{
			num = ft_atoi(av[*i]);
			if (num > 0 && ft_is_pint(num))
			{
				fl->n++;
				if (*i + 1 < ac && ft_strcmp(av[*i + 1], "-v")
					&& ft_strcmp(av[*i + 1], "-l")
					&& ft_strcmp(av[*i + 1], "-dump")
					&& ft_strcmp(av[*i + 1], "-n")
					&& ft_strcmp(av[*i + 1], "-s"))
					return (0);
				else
					return (ft_puterrendl("Error: wrong argument"));
			}
		}
	}
	return (ft_puterrendl("Error: wrong argument"));
}

static int	verif_fl(t_flags *fl)
{
	if (fl->nplayers > 0 && fl->nplayers <= MAX_PLAYERS)
	{
		fl->mem_for_champ = MEM_SIZE / fl->nplayers;
		return (0);
	}
	else
		return (ft_puterrendl("Error: wrong number of champion(s)"));
}

int			parse_flags(t_flags *fl, int ac, char **av)
{
	int	i;

	i = 0;
	*fl = (t_flags){0, -1, 0, 0, 0, 0, 0, 0, 1, CYCLE_TO_DIE, 0, 0, 0, 50, 0,
					0};
	while (++i < ac)
		if (!ft_strcmp("-v", av[i]) && fl->dump == -1)
			fl->v = 1;
		else if (!ft_strcmp("-l", av[i]))
			fl->l = 1;
		else if (!ft_strcmp("-s", av[i]))
			fl->s = 1;
		else if (!ft_strcmp("-a", av[i]))
			fl->a = 1;
		else if (!ft_strcmp("-dump", av[i]))
		{
			if (handle_dump(ac, av, &i, fl))
				return (1);
		}
		else if (!ft_strcmp("-n", av[i]) && handle_n(ac, av, &i, fl))
			return (1);
		else
			fl->nplayers++;
	return (verif_fl(fl));
}
