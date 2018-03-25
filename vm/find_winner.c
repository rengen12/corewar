/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_winner.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amichak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/24 14:39:00 by amichak           #+#    #+#             */
/*   Updated: 2018/03/24 14:39:00 by amichak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_player	*find_winner(t_player *pls)
{
	t_player	*winner;

	winner = pls;
	if (pls)
		while (pls)
		{
			if (pls->last_live >= winner->last_live || (winner->last_live == 0
														&& pls->is_last))
				winner = pls;
			pls = pls->next;
		}
	return (winner);
}
