/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amichak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/24 15:32:00 by amichak           #+#    #+#             */
/*   Updated: 2018/03/24 15:32:00 by amichak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int	player_id_exist(t_player *pls, int id)
{
	while (pls)
	{
		if (pls->id == id)
			return (1);
		pls = pls->next;
	}
	return (0);
}

int			player_n_exist(t_player *pls, unsigned int n)
{
	while (pls)
	{
		if (pls->n == n)
			return (1);
		pls = pls->next;
	}
	return (0);
}

int			find_available_player_n(t_player *pls)
{
	short int	i;

	i = 1;
	while (1)
	{
		if (player_id_exist(pls, i))
			i++;
		else
			return (i);
	}
}

void		reset_players_live(t_player *pls)
{
	if (pls)
		while (pls)
		{
			pls->n_lives = 0;
			pls = pls->next;
		}
}
