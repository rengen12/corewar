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

t_proc	*init_proc_data(unsigned int pc, t_player *pl, t_flags *fl)
{
	t_proc	*proc;
	int		i;
	int		y;

	if (!(proc = (t_proc *)malloc(sizeof(t_proc))))
		return (NULL);
	proc->carry = 1;
	proc->pc = pc;
	proc->pl = pl;
	proc->wait = 0;
	proc->cyc_to_die = CYCLE_TO_DIE;
	proc->id = fl->proc_num++;
	proc->next = 0;
	i = 0;
	while (i < REG_NUMBER)
	{
		y = 0;
		/*while (y < REG_SIZE)
			proc->regs[i][y++] = 0;*/
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
		prcs->regs[0] = (unsigned int)fl->nplayers;
		//parse_inttochar(&nplayers, prcs->regs[0], 4);
		pls = pls->next;
	}
	return (prcs);
}

int		handle_process(unsigned char *m, t_proc *cur, t_proc **head, t_flags *fl)
{
	int 	res;

	res = 0;
	if (LIVE == (m[cur->pc]))
		res = handle_live(cur);
	else if (LD == (m[cur->pc]))
		res = handle_ld(m, cur);
	else if (ST == (m[cur->pc]))
		res = handle_st();
	else if (ADD == (m[cur->pc]))
		res = handle_add();
	else if (SUB == (m[cur->pc]))
		res = handle_sub();
	else if (AND == (m[cur->pc]))
		res = handle_and();
	else if (OR == (m[cur->pc]))
		res = handle_or();
	else if (XOR == (m[cur->pc]))
		res = handle_xor();
	else if (ZJMP == (m[cur->pc]))
		res = handle_zjmp(m, cur);
	else if (LDI == (m[cur->pc]))
		res = handle_ldi();
	else if (STI == (m[cur->pc]))
		res = handle_sti();
	else if (FORK == (m[cur->pc]))
		res = handle_fork(m, cur, head, fl);
	else if (LLD == (m[cur->pc]))
		res = handle_lld();
	else if (LLDI == (m[cur->pc]))
		res = handle_lldi();
	else if (LFORK == (m[cur->pc]))
		res = handle_lfork(m, cur, head, fl);
	else if (AFF == (m[cur->pc]))
		res = handle_aff(m, cur, *fl);
	else
		cur->pc++;
	(void)head;
	return (res);
}
