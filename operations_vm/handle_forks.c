/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_forks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amichak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 17:42:00 by amichak           #+#    #+#             */
/*   Updated: 2018/03/18 17:42:00 by amichak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../corewar.h"

static void	cp_proc_data(t_proc *dest, t_proc *src)
{
	int	i;

	i = 0;
	dest->carry = src->carry;
	dest->cyc_to_die = src->cyc_to_die;
	while (i < REG_NUMBER)
	{
		dest->regs[i] = src->regs[i];
		i++;
	}
}

void		handle_fork(unsigned char *m, t_proc *p, t_proc **head, t_flags *fl)
{
	unsigned int	arg;
	unsigned char	pm[2];
	int				addr;

	p->pc_old = p->pc;
	pm[0] = m[(p->pc + 1) % MEM_SIZE];
	pm[1] = m[(p->pc + 2) % MEM_SIZE];
	parse_strtoint(&arg, pm, 2);
	addr = (p->pc + (short)arg % IDX_MOD) % MEM_SIZE;
	if (addr < 0)
		addr = MEM_SIZE + addr;
	add_proc(head, init_proc_data(addr, p->pl, fl));
	cp_proc_data(*head, p);
	proc_caret_add((*head)->pc);
	p->pc = (p->pc + 3) % MEM_SIZE;
}

void		handle_lfork(unsigned char *m, t_proc *p, t_proc **head,
						t_flags *fl)
{
	unsigned int	arg;
	unsigned char	pm[2];
	int				addr;

	p->pc_old = p->pc;
	pm[0] = m[(p->pc + 1) % MEM_SIZE];
	pm[1] = m[(p->pc + 2) % MEM_SIZE];
	parse_strtoint(&arg, pm, 2);
	addr = (p->pc + (short)arg) % MEM_SIZE;
	if (addr < 0)
		addr = MEM_SIZE + addr;
	add_proc(head, init_proc_data(addr, p->pl, fl));
	cp_proc_data(*head, p);
	proc_caret_add((*head)->pc);
	p->pc = (p->pc + 3) % MEM_SIZE;
}
