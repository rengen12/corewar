/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amichak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 19:27:00 by amichak           #+#    #+#             */
/*   Updated: 2018/03/06 19:27:00 by amichak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_proc	*init_proc_data(int pc, t_player *pl, t_flags *fl)
{
	t_proc	*proc;
	int		i;
	int		y;

	if (!(proc = (t_proc *)malloc(sizeof(t_proc))))
		return (NULL);
	proc->carry = 0;
	proc->pc = pc;
	proc->pc_old = 0;
	proc->pl = pl;
	proc->wait = 0;
	proc->cyc_to_die = fl->cycle_to_die_def;
	proc->id = fl->proc_num++;
	proc->next = 0;
	i = 0;
	while (i < REG_NUMBER)
	{
		y = 0;
		proc->regs[i] = 0;
		i++;
	}
	return (proc);
}

void	add_proc(t_proc **head, t_proc *new)
{
	if (head && new)
	{
		new->next = *head;
		*head = new;
	}
}

t_proc	*create_procs(t_player *pls, t_flags *fl)
{
	t_proc	*prcs;

	prcs = NULL;
	while (pls)
	{
		add_proc(&prcs, init_proc_data(pls->st_code, pls, fl));
		prcs->regs[0] = (unsigned int)((short)0 - pls->id);
		//parse_inttochar(&nplayers, prcs->regs[0], 4);
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

void	delete_proc(t_proc **head, t_proc **to_del)
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

//5 arg
int		handle_process(unsigned char *m, t_proc *cur, t_proc **head, t_flags *fl, t_player *pls, int cycles)
{
	int 	res;

	res = 0;
	if (LIVE == (m[cur->pc]))
		handle_live(m, cur, pls, fl, cycles);//5 arg
	else if (LD == (m[cur->pc]))
		handle_ld(m, cur);
	else if (ST == (m[cur->pc]))
		handle_st(m, cur, *fl);
	else if (ADD == (m[cur->pc]))
		handle_add(m, cur);
	else if (SUB == (m[cur->pc]))
		handle_sub(m, cur);
	else if (AND == (m[cur->pc]))
		handle_and(m, cur);
	else if (OR == (m[cur->pc]))
		handle_or(m, cur);
	else if (XOR == (m[cur->pc]))
		handle_xor(m, cur);
	else if (ZJMP == (m[cur->pc]))
		handle_zjmp(m, cur);
	else if (LDI == (m[cur->pc]))
		handle_ldi(m, cur);
	else if (STI == (m[cur->pc]))
		handle_sti(m, cur, *fl);
	else if (FORK == (m[cur->pc]))
		handle_fork(m, cur, head, fl);
	else if (LLD == (m[cur->pc]))
		handle_lld(m, cur);
	else if (LLDI == (m[cur->pc]))
		handle_lldi(m, cur);
	else if (LFORK == (m[cur->pc]))
		handle_lfork(m, cur, head, fl);
	else if (AFF == (m[cur->pc]))
		handle_aff(m, cur, *fl);
	else
	{
		//proc_caret_rem(cur->pc);
		cur->pc_old = cur->pc;
		cur->pc = (cur->pc + 1) % MEM_SIZE;
		//proc_caret_add(cur->pc);
	}
	proc_caret_rem(cur->pc_old);
	proc_caret_add(cur->pc);
	cur->pc_old = 0;
	refresh();
	return (res);
}
