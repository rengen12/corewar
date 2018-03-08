/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op1.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amichak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 14:41:00 by amichak           #+#    #+#             */
/*   Updated: 2018/03/07 14:41:00 by amichak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		offset(unsigned char opcode)
{
	int 	res;

	res = 0;
	if (opcode >> 6 == 1)
		return (1);
	else if (opcode >> 2 == 21)
		return (3);
	return (res);
}

int		handle_live(t_proc *p)
{
	p->cyc_to_die = CYCLE_TO_DIE;
	p->wait = 10;
	p->pc = (p->pc + 5) % MEM_SIZE;
	//1 arg for reporting player num
	return (0);
}

int		handle_ld(unsigned char *m, t_proc *prc)
{

	return (0);
}

int		handle_st()
{
	return (0);
}

int		handle_add(unsigned char *m, t_proc *p)
{
	p->wait = 10;
	if (m[(p->pc + 1) % MEM_SIZE] != 84 || \
			m[(p->pc + 2) % MEM_SIZE] > REG_NUMBER || \
			m[(p->pc + 2) % MEM_SIZE] < 1 || \
			m[(p->pc + 3) % MEM_SIZE] > REG_NUMBER || \
			m[(p->pc + 3) % MEM_SIZE] < 1 || \
		m[(p->pc + 4) % MEM_SIZE] > REG_NUMBER || m[(p->pc + 4) % MEM_SIZE] < 1)
	{
		p->carry = 0;
		p->pc = (p->pc + 2) % MEM_SIZE;
		return (0);
	}
	p->regs[m[(p->pc + 4) % MEM_SIZE]] = p->regs[m[(p->pc + 2) % MEM_SIZE]] +
										 p->regs[m[(p->pc + 3) % MEM_SIZE]];
	p->pc = (p->pc + 2 + offset(m[(p->pc + 1) % MEM_SIZE])) % MEM_SIZE;
	p->carry = 1;
	return (0);
}

int		handle_sub(unsigned char *m, t_proc *p)
{
	p->wait = 10;
	if (m[(p->pc + 1) % MEM_SIZE] != 84 || \
			m[(p->pc + 2) % MEM_SIZE] > REG_NUMBER || \
			m[(p->pc + 2) % MEM_SIZE] < 1 || \
			m[(p->pc + 3) % MEM_SIZE] > REG_NUMBER || \
			m[(p->pc + 3) % MEM_SIZE] < 1 || \
		m[(p->pc + 4) % MEM_SIZE] > REG_NUMBER || m[(p->pc + 4) % MEM_SIZE] < 1)
	{
		p->carry = 0;
		p->pc = (p->pc + 2) % MEM_SIZE;
		return (0);
	}
	p->regs[m[(p->pc + 4) % MEM_SIZE]] = p->regs[m[(p->pc + 2) % MEM_SIZE]] -
			p->regs[m[(p->pc + 3) % MEM_SIZE]];
	p->pc = (p->pc + 2 + offset(m[(p->pc + 1) % MEM_SIZE])) % MEM_SIZE;
	p->carry = 1;
	return (0);
}

int		handle_and(unsigned char *m, t_proc *p)
{

	return (0);
}
int		handle_or()
{
	return (0);
}
int		handle_xor()
{
	return (0);
}
int		handle_zjmp(unsigned char *m, t_proc *p)
{
	short int		arg;
	unsigned char	pm[2];

	pm[0] = m[(p->pc + 1) % MEM_SIZE];
	pm[1] = m[(p->pc + 2) % MEM_SIZE];
	parse_strtoint(&arg, pm, 2);//test it
	p->wait = 20;
	if (p->carry)
	{
		p->pc = (p->pc + arg) % MEM_SIZE;
		if (p->pc < 0)
			p->pc = MEM_SIZE + p->pc;
	}
	return (0);
}
int		handle_ldi()
{
	return (0);
}
int		handle_sti()
{
	return (0);
}

int		handle_fork(unsigned char *m, t_proc *p, t_proc **head, t_flags *fl)
{
	unsigned int	arg;
	unsigned char	pm[2];

	pm[0] = m[(p->pc + 1) % MEM_SIZE];
	pm[1] = m[(p->pc + 2) % MEM_SIZE];
	parse_strtoint(&arg, pm, 2); //test it
	p->wait = 800;
	add_proc(head, init_proc_data((p->pc + arg % IDX_MOD) % MEM_SIZE, p->pl, fl));
	p->pc = (p->pc + 3) % MEM_SIZE;
	return (0);
}

int		handle_lld()
{
	return (0);
}
int		handle_lldi()
{
	return (0);
}

int		handle_lfork(unsigned char *m, t_proc *p, t_proc **head, t_flags *fl)
{
	unsigned int	arg;
	unsigned char	pm[2];

	pm[0] = m[(p->pc + 1) % MEM_SIZE];
	pm[1] = m[(p->pc + 2) % MEM_SIZE];
	parse_strtoint(&arg, pm, 2);//test it
	p->wait = 1000;
	add_proc(head, init_proc_data((p->pc + arg) % MEM_SIZE, p->pl, fl));
	p->pc = (p->pc + 3) % MEM_SIZE;
	return (0);
}

int		handle_aff(unsigned char *m, t_proc *p, t_flags fl)
{
	/*if (m[(p->pc + 1) % MEM_SIZE] != 64 || m[(p->pc + 2) % MEM_SIZE] < 1 || \
			m[(p->pc + 2) % MEM_SIZE] > REG_NUMBER)
		return (1);*/
	p->wait = 2;
	if (fl.a && m[(p->pc + 1) % MEM_SIZE] >> 6 == 1 && \
			m[(p->pc + 2) % MEM_SIZE] < 1 && \
			m[(p->pc + 2) % MEM_SIZE] > REG_NUMBER)
	{
		ft_putstr("aff: ");
		ft_putnbr(p->regs[m[(p->pc + 2) % MEM_SIZE] - 1]);
		ft_putchar('\n');
	}
	p->pc = (p->pc + 2 + offset(m[(p->pc + 1) % MEM_SIZE])) % MEM_SIZE;
	return (0);
}
