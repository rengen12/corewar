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
	int 	i;

	i = 0;
	dest->carry = src->carry;
	dest->cyc_to_die = src->cyc_to_die;
	while (i < REG_NUMBER)
	{
		dest->regs[i] = src->regs[i];
		i++;
	}
}

/*verif*/
int		handle_fork(unsigned char *m, t_proc *p, t_proc **head, t_flags *fl)
{
	unsigned int	arg;
	unsigned char	pm[2];
	unsigned int	addr;

	p->pc_old = p->pc;
	pm[0] = m[(p->pc + 1) % MEM_SIZE];
	pm[1] = m[(p->pc + 2) % MEM_SIZE];
	parse_strtoint(&arg, pm, 2);

	//add_proc(head, init_proc_data((p->pc + arg % IDX_MOD) % MEM_SIZE, p->pl, fl)); //negative??
	addr = (p->pc + arg % IDX_MOD) % MEM_SIZE;
	if (arg > 32767)
		addr = MEM_SIZE + (arg % IDX_MOD) - IDX_MOD + p->pc;
	add_proc(head, init_proc_data(addr, p->pl, fl)); //negative??
	cp_proc_data(*head, p);
	proc_caret_add((*head)->pc);
	p->pc = (p->pc + 3) % MEM_SIZE;
	return (0);
}

/*verif*/
int		handle_lfork(unsigned char *m, t_proc *p, t_proc **head, t_flags *fl)
{
	unsigned int	arg;
	unsigned char	pm[2];

	p->pc_old = p->pc;
	pm[0] = m[(p->pc + 1) % MEM_SIZE];
	pm[1] = m[(p->pc + 2) % MEM_SIZE];
	parse_strtoint(&arg, pm, 2);
	add_proc(head, init_proc_data((p->pc + arg) % MEM_SIZE, p->pl, fl));//negative??
	cp_proc_data(*head, p);
	proc_caret_add((*head)->pc);
	p->pc = (p->pc + 3) % MEM_SIZE;
	return (0);
}
