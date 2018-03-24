/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amichak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/24 15:42:00 by amichak           #+#    #+#             */
/*   Updated: 2018/03/24 15:42:00 by amichak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_proc			*init_proc_data(int pc, t_player *pl, t_flags *fl)
{
	t_proc	*proc;
	int		i;

	if (!(proc = (t_proc *)malloc(sizeof(t_proc))))
		return (NULL);
	proc->carry = 0;
	proc->pc = pc;
	proc->pc_old = 0;
	proc->pl = pl;
	proc->to_ex = 0;
	proc->wait = 0;
	proc->cyc_to_die = fl->cycle_to_die_def;
	proc->id = fl->proc_num++;
	proc->next = 0;
	i = 0;
	while (i < REG_NUMBER)
		proc->regs[i++] = 0;
	return (proc);
}

void			add_proc(t_proc **head, t_proc *new)
{
	if (head && new)
	{
		new->next = *head;
		*head = new;
	}
}

t_proc			*create_first_procs(t_player *pls, t_flags *fl)
{
	t_proc	*prcs;

	prcs = NULL;
	while (pls)
	{
		add_proc(&prcs, init_proc_data(pls->st_code, pls, fl));
		prcs->regs[0] = pls->n;
		pls = pls->next;
	}
	return (prcs);
}

static t_proc	*find_prev_proc(t_proc *head, t_proc *next)
{
	while (head && head->next)
	{
		if (head->next->id == next->id)
			return (head);
		head = head->next;
	}
	return (NULL);
}

void			delete_proc(t_proc **head, t_proc **to_del)
{
	t_proc	*prev;
	t_proc	*temp;

	if (head && to_del && *head && *to_del)
	{
		proc_caret_rem((*to_del)->pc);
		if ((prev = find_prev_proc(*head, *to_del)))
			prev->next = (*to_del)->next;
		else
			*head = (*to_del)->next;
		temp = (*to_del)->next;
		free(*to_del);
		*to_del = temp;
	}
}
