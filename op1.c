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

int		offset(unsigned char opcode, int size)
{
	int 	res;
	int 	mask;
	int 	offset;

	offset = 6;
	mask = 192;
	res = 0;
	while (size--)
	{
		if ((opcode & mask) >> offset == REG_CODE)
			res += REG_S;
		else if ((opcode & mask) >> offset == IND_CODE)
			res += IND_SIZE;
		else if ((opcode & mask) >> offset == DIR_CODE)
			res += DIR_SIZE;
		mask >>= 2;
		offset -= 2;
	}
	return (res);
}

unsigned char	get_m_v(unsigned char *m, int pc)
{
	return (m[pc % MEM_SIZE]);
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
	if (offset(get_m_v(m, p->pc + 1), 3) != 3  || \
		m[(p->pc + 2) % MEM_SIZE] > REG_NUMBER || \
		m[(p->pc + 2) % MEM_SIZE] < 1 || \
		m[(p->pc + 3) % MEM_SIZE] > REG_NUMBER || \
		m[(p->pc + 3) % MEM_SIZE] < 1 || \
		m[(p->pc + 4) % MEM_SIZE] > REG_NUMBER || m[(p->pc + 4) % MEM_SIZE] < 1)
	{
		p->carry = 0;
		p->pc = (p->pc + 2 + offset(get_m_v(m, p->pc + 1), 3)) % MEM_SIZE;
		return (0);
	}
	p->regs[m[(p->pc + 4) % MEM_SIZE]] = p->regs[m[(p->pc + 2) % MEM_SIZE]] +	//sing unsign?
										 p->regs[m[(p->pc + 3) % MEM_SIZE]];
	p->pc = (p->pc + 2 + offset(get_m_v(m, p->pc + 1), 3)) % MEM_SIZE;
	p->carry = 1;
	return (0);
}

int		handle_sub(unsigned char *m, t_proc *p)
{
	p->wait = 10;
	if (offset(get_m_v(m, p->pc + 1), 3) != 3  || \
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
	p->regs[m[(p->pc + 4) % MEM_SIZE]] = p->regs[m[(p->pc + 2) % MEM_SIZE]] -	//sing unsign?
			p->regs[m[(p->pc + 3) % MEM_SIZE]];
	p->pc = (p->pc + 2 + offset(get_m_v(m, p->pc + 1), 3)) % MEM_SIZE;
	p->carry = 1;
	return (0);
}

void	get_v_opcode(unsigned int *res, unsigned int opcode, unsigned char *m, t_proc *p)
{
	unsigned char	pm[4];

	opcode = (opcode & 192) >> 6;
	if (opcode == T_REG)
	{
		*res = m[p->pc];
		++p->pc %= MEM_SIZE;
	}
	else if (opcode == T_IND)
	{
		pm[0] = m[p->pc];
		pm[1] = m[(p->pc + 1) % MEM_SIZE];
		parse_strtoint(res, pm, IND_SIZE);
		p->pc = (p->pc + IND_SIZE) % MEM_SIZE;
	}
	else if (opcode == T_DIR)
	{
		pm[0] = m[p->pc];
		pm[1] = m[(p->pc + 1) % MEM_SIZE];
		pm[2] = m[(p->pc + 2) % MEM_SIZE];
		pm[3] = m[(p->pc + 3) % MEM_SIZE];
		parse_strtoint(res, pm, DIR_SIZE);
		p->pc = (p->pc + DIR_SIZE) % MEM_SIZE;
	}
}

int		handle_and(unsigned char *m, t_proc *p)
{
	unsigned int 	op[3];
	unsigned int	opcode;
	int 			i;

	i = 0;
	p->wait = 6;
	opcode = m[(p->pc + 1) % MEM_SIZE];
	p->pc = (p->pc + 2) % MEM_SIZE;
	while (i < 3)
	{
		get_v_opcode(&op[i++], opcode, m, p);
		opcode <<= 2;
	}
	if ((opcode & 192) >> 6 == T_REG && op[0] >= 1 && op[0] <= 16)
	{
		if (op[0] >= 1 && op[0] <= 16)
			op[0] = p->regs[op[0] - 1];
		else
			return (0);
	}
	if ((opcode & 48) >> 4 == T_REG && op[0] >= 1 && op[0] <= 16)
	{
		if (op[1] >= 1 && op[1] <= 16)
			op[1] = p->regs[op[1] - 1];
		else
			return (0);
	}
	if ((get_m_v(m, p->pc) & 12) >> 2 == REG_CODE)
		p->regs[op[2] - 1] = op[0] & op[1];
	return (0);
}

int		handle_or(unsigned char *m, t_proc *p)
{
	unsigned int 	op[3];
	unsigned int	opcode;
	int 			i;

	i = 0;
	p->wait = 6;
	opcode = m[(p->pc + 1) % MEM_SIZE];
	p->pc = (p->pc + 2) % MEM_SIZE;
	while (i < 3)
	{
		get_v_opcode(&op[i++], opcode, m, p);
		opcode <<= 2;
	}
	if ((opcode & 192) >> 6 == T_REG && op[0] >= 1 && op[0] <= 16)
	{
		if (op[0] >= 1 && op[0] <= 16)
			op[0] = p->regs[op[0] - 1];
		else
			return (0);
	}
	if ((opcode & 48) >> 4 == T_REG && op[0] >= 1 && op[0] <= 16)
	{
		if (op[1] >= 1 && op[1] <= 16)
			op[1] = p->regs[op[1] - 1];
		else
			return (0);
	}
	if ((get_m_v(m, p->pc) & 12) >> 2 == REG_CODE)
		p->regs[op[2] - 1] = op[0] | op[1];
	return (0);
}

int		handle_xor(unsigned char *m, t_proc *p)
{
	unsigned int 	op[3];
	unsigned int	opcode;
	int 			i;

	i = 0;
	p->wait = 6;
	opcode = m[(p->pc + 1) % MEM_SIZE];
	p->pc = (p->pc + 2) % MEM_SIZE;
	while (i < 3)
	{
		get_v_opcode(&op[i++], opcode, m, p);
		opcode <<= 2;
	}
	if ((opcode & 192) >> 6 == T_REG)
	{
		if (op[0] >= 1 && op[0] <= 16)
			op[0] = p->regs[op[0] - 1];
		else
			return (0);
	}
	if ((opcode & 48) >> 4 == T_REG)
	{
		if (op[1] >= 1 && op[1] <= 16)
			op[1] = p->regs[op[1] - 1];
		else
			return (0);
	}
	if ((get_m_v(m, p->pc) & 12) >> 2 == REG_CODE)
		p->regs[op[2] - 1] = op[0] ^ op[1];
	return (0);
}

int		handle_zjmp(unsigned char *m, t_proc *p)
{
	short int		arg;
	unsigned char	pm[2];

	p->wait = 20;
	pm[0] = m[(p->pc + 1) % MEM_SIZE];
	pm[1] = m[(p->pc + 2) % MEM_SIZE];
	parse_strtoint(&arg, pm, 2);//test it
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
	if (m[(p->pc + 1) % MEM_SIZE] >> 6 == 1)
	{
		if (fl.a && m[(p->pc + 2) % MEM_SIZE] < 1 && \
			m[(p->pc + 2) % MEM_SIZE] > REG_NUMBER)
		{
			ft_putstr("aff: ");
			ft_putnbr(p->regs[m[(p->pc + 2) % MEM_SIZE] - 1]);
			ft_putchar('\n');
		}
	}
	p->pc = (p->pc + 2 + offset(get_m_v(m, p->pc + 1), 1)) % MEM_SIZE;
	return (0);
}
