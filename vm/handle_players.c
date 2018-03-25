/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_players.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amichak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 16:10:00 by amichak           #+#    #+#             */
/*   Updated: 2018/03/05 16:10:00 by amichak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		*delete_players(t_player **pls)
{
	if (pls && *pls)
	{
		if ((*pls)->next)
			delete_players(&((*pls)->next));
		free(*pls);
		*pls = NULL;
	}
	return (NULL);
}

int			add_pl(t_player **pls, t_player *pl, char *path)
{
	t_player	*temppl;

	if (pl && pls)
	{
		temppl = *pls;
		pl->next = NULL;
		if (temppl)
		{
			while (temppl->next)
				temppl = temppl->next;
			temppl->next = pl;
		}
		else
			*pls = pl;
	}
	else
	{
		if (errno)
			perror(path);
		delete_players(pls);
		return (1);
	}
	return (0);
}

static void	handle_n(char **av, unsigned int *pl_num, int *i)
{
	if (!ft_strcmp("-n", av[(*i)]))
		*pl_num = (unsigned int)ft_atoi(av[++(*i)]);
	else if (!ft_strcmp("-dump", av[(*i)]))
		++(*i);
}

static int	is_right_fl(char *s)
{
	return (!ft_strcmp("-dump", s) || !ft_strcmp("-n", s) ||
			!ft_strcmp("-v", s) || !ft_strcmp("-l", s) ||
			!ft_strcmp("-s", s));
}

t_player	*handle_players(int ac, char **av, t_flags *fl, unsigned char *mem)
{
	t_player		*pls;
	int				i;
	unsigned int	pl_num;
	unsigned int	cur_mem;

	cur_mem = 0;
	i = 0;
	pl_num = 0;
	pls = NULL;
	while (++i < ac)
		if (is_right_fl(av[i]))
			handle_n(av, &pl_num, &i);
		else
		{
			if (pl_num == 0)
				pl_num = (unsigned int)find_available_player_n(pls);
			else if (player_n_exist(pls, pl_num))
				return (delete_players(&pls));
			if (add_pl(&pls, handle_player(av[i], mem, cur_mem, pl_num), av[i]))
				return (NULL);
			cur_mem += fl->mem_for_champ;
			pl_num = 0;
		}
	return (pls);
}
