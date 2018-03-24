/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amichak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/24 14:31:00 by amichak           #+#    #+#             */
/*   Updated: 2018/03/24 14:31:00 by amichak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int	need_decreace_cycle_to_die(t_player *pls, t_flags *fl)
{
	unsigned int	res;
	static int		max_checks;

	res = 0;
	max_checks++;
	if (max_checks >= MAX_CHECKS)
	{
		max_checks = 0;
		return (1);
	}
	if (fl->cycle_to_die_cur >= NBR_LIVE)
	{
		max_checks = 0;
		fl->cycle_to_die_cur = 0;
		return (1);
	}
	fl->cycle_to_die_cur = 0;
	while (pls)
	{
		res += pls->n_lives;
		pls->n_lives = 0;
		pls = pls->next;
	}
	return (res >= NBR_LIVE ? 1 : 0);
}

static void	handle_events()
{
	//int 	ch;

	//ch = getch();
	//if (ch == 'w')
		//exit(0);
}

void		update_cur(t_proc **cur, t_proc **head, t_flags *fl,
						unsigned int *lc)
{
	if (*cur)
	{
		(*cur)->cyc_to_die--;
		*cur = (*cur)->next;
	}
	if (!(*cur))
	{
		*cur = *head;
		fl->cycles++;
		(*lc)++;
		service_inf(count_proc(*head), fl->pls, fl);
		reset_players_live(fl->pls);
		handle_events();
		refresh();
	}
}

int			handle_one_iter(t_proc **cur, t_flags *fl, unsigned int *lc,
						t_proc **head)
{
	if (!(*cur)->next && !(*lc = 0))
		if (need_decreace_cycle_to_die(fl->pls, fl))
			fl->cycle_to_die_def -= CYCLE_DELTA;
	if (fl->cycle_to_die_def < 0 && (*cur = *head))
		while (*cur)
			delete_proc(head, cur);
	if (*cur && (*cur)->cyc_to_die <= 0)
	{
		delete_proc(head, cur);
		(!*cur) ? *cur = *head : 0;
		return (1);
	}
	return (0);
}

void		start_game(unsigned char *mem, t_proc **head, t_flags *fl,
						t_proc *cur)
{
	unsigned int	local_cycle;

	local_cycle = 0;
	init_visual(fl, mem, *head, fl->pls);
	while (cur)
	{
		if (fl->cycles == fl->dump && print_mem(mem))
			break ;
		if (local_cycle && (local_cycle % fl->cycle_to_die_def) == 0)
		{
			if (handle_one_iter(&cur, fl, &local_cycle, head))
				continue ;
		}
		else
		{
			if (cur->wait <= 0)
				set_waiting(mem, cur);
			if (--cur->wait <= 0)
				handle_process(mem, cur, head, fl);
		}
		update_cur(&cur, head, fl, &local_cycle);
	}
	end_visual(fl, find_winner(fl->pls));
}
