/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_live.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amichak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 17:43:00 by amichak           #+#    #+#             */
/*   Updated: 2018/03/18 17:43:00 by amichak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../corewar.h"

static t_player	*find_pl_n(t_player *pls, unsigned int n)
{
	while (pls)
	{
		if (pls->n == n)
			return (pls);
		pls = pls->next;
	}
	return (pls);
}

void			handle_live(unsigned char *m, t_proc *p, t_player *pls,
							t_flags *fl)
{
	unsigned int	val;
	unsigned char	pm[4];
	t_player		*pl;

	p->pc_old = p->pc;
	p->pc = (p->pc + 1) % MEM_SIZE;
	pm[0] = m[p->pc];
	pm[1] = m[(p->pc + 1) % MEM_SIZE];
	pm[2] = m[(p->pc + 2) % MEM_SIZE];
	pm[3] = m[(p->pc + 3) % MEM_SIZE];
	p->cyc_to_die = fl->cycle_to_die_def;
	parse_strtoint(&val, pm, 4);
	if ((pl = find_pl_n(pls, val)))
	{
		pl->last_live = fl->cycles;
		pl->n_lives++;
	}
	fl->cycle_to_die_cur++;
	p->pc = (p->pc + 4) % MEM_SIZE;
}
