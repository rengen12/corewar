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

static void	handle_process1(unsigned char *m, t_proc *cur, t_flags *fl)
{
	if (LD == cur->to_ex)
		handle_ld(m, cur);
	else if (ST == cur->to_ex)
		handle_st(m, cur, *fl);
	else if (ADD == cur->to_ex)
		handle_add(m, cur);
	else if (SUB == cur->to_ex)
		handle_sub(m, cur);
	else if (AND == cur->to_ex)
		handle_and(m, cur);
	else if (OR == cur->to_ex)
		handle_or(m, cur);
	else if (XOR == cur->to_ex)
		handle_xor(m, cur);
	else if (ZJMP == cur->to_ex)
		handle_zjmp(m, cur);
	else if (LDI == cur->to_ex)
		handle_ldi(m, cur);
	else if (STI == cur->to_ex)
		handle_sti(m, cur, *fl);
	else if (LLD == cur->to_ex)
		handle_lld(m, cur);
	else if (LLDI == cur->to_ex)
		handle_lldi(m, cur);
}

void		handle_process(unsigned char *m, t_proc *cur, t_proc **head,
					t_flags *fl)
{
	if (LIVE == cur->to_ex)
		handle_live(m, cur, fl->pls, fl);
	else if (LD == cur->to_ex || ST == cur->to_ex || ADD == cur->to_ex ||
			SUB == cur->to_ex || AND == cur->to_ex || OR == cur->to_ex ||
			XOR == cur->to_ex || ZJMP == cur->to_ex || LDI == cur->to_ex ||
			STI == cur->to_ex || LLD == cur->to_ex || LLDI == cur->to_ex)
		handle_process1(m, cur, fl);
	else if (FORK == cur->to_ex)
		handle_fork(m, cur, head, fl);
	else if (LFORK == cur->to_ex)
		handle_lfork(m, cur, head, fl);
	else if (AFF == cur->to_ex)
		handle_aff(m, cur, *fl);
	else
	{
		cur->pc_old = cur->pc;
		cur->pc = (cur->pc + 1) % MEM_SIZE;
	}
	proc_caret_rem(cur->pc_old);
	proc_caret_add(cur->pc);
	cur->pc_old = 0;
	cur->to_ex = 0;
}
