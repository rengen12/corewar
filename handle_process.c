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

	if (!(proc = (t_proc *)malloc(sizeof(t_proc))))
		return (NULL);
	proc->carry = 0;
	proc->pc = pc;
	proc->pc_old = 0;
	proc->pl = pl;
	proc->opcode_to_exec = 0;
	proc->wait = 0;
	proc->cyc_to_die = fl->cycle_to_die_def;
	proc->id = fl->proc_num++;
	proc->next = 0;
	i = 0;
	while (i < REG_NUMBER)
		proc->regs[i++] = 0;
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

int		handle_process(unsigned char *m, t_proc *cur, t_proc **head, t_flags *fl, t_player *pls)
{
	int 	res;

	res = 0;
	if (LIVE == cur->opcode_to_exec)
		handle_live(m, cur, pls, fl);
	else if (LD == cur->opcode_to_exec)
		handle_ld(m, cur);
	else if (ST == cur->opcode_to_exec)
		handle_st(m, cur, *fl);
	else if (ADD == cur->opcode_to_exec)
		handle_add(m, cur);
	else if (SUB == cur->opcode_to_exec)
		handle_sub(m, cur);
	else if (AND == cur->opcode_to_exec)
		handle_and(m, cur);
	else if (OR == cur->opcode_to_exec)
		handle_or(m, cur);
	else if (XOR == cur->opcode_to_exec)
		handle_xor(m, cur);
	else if (ZJMP == cur->opcode_to_exec)
		handle_zjmp(m, cur);
	else if (LDI == cur->opcode_to_exec)
		handle_ldi(m, cur);
	else if (STI == cur->opcode_to_exec)
		handle_sti(m, cur, *fl);
	else if (FORK == cur->opcode_to_exec)
		handle_fork(m, cur, head, fl);
	else if (LLD == cur->opcode_to_exec)
		handle_lld(m, cur);
	else if (LLDI == cur->opcode_to_exec)
		handle_lldi(m, cur);
	else if (LFORK == cur->opcode_to_exec)
		handle_lfork(m, cur, head, fl);
	else if (AFF == cur->opcode_to_exec)
		handle_aff(m, cur, *fl);
	else
	{
		cur->pc_old = cur->pc;
		cur->pc = (cur->pc + 1) % MEM_SIZE;
	}
	proc_caret_rem(cur->pc_old);
	proc_caret_add(cur->pc);
	cur->pc_old = 0;
	cur->opcode_to_exec = 0;
	refresh();
	return (res);
}
