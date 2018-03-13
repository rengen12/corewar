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


//correct func behavior when acb changed. When acb incorrect - dont return smth and continue handling params

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

unsigned int	get_v_acb(unsigned int opcode, unsigned char *m, t_proc *p, int dir_size)
{
	unsigned char	pm[4];
	unsigned int	res;

	opcode = (opcode & 192) >> 6;
	res = 0;
	if (opcode == T_REG)
	{
		res = m[p->pc];
		p->pc = (p->pc + 1) % MEM_SIZE;
	}
	else if (opcode == T_IND)
	{
		pm[0] = m[p->pc];
		pm[1] = m[(p->pc + 1) % MEM_SIZE];
		parse_strtoint(&res, pm, 2);
		p->pc = (p->pc + IND_SIZE) % MEM_SIZE;
	}
	else if (opcode == T_DIR)
	{
		pm[0] = m[p->pc];
		pm[1] = m[(p->pc + 1) % MEM_SIZE];
		if (dir_size > 2)
		{
			pm[2] = m[(p->pc + 2) % MEM_SIZE];
			pm[3] = m[(p->pc + 3) % MEM_SIZE];
		}
		parse_strtoint(&res, pm, dir_size);
		p->pc = (p->pc + dir_size) % MEM_SIZE;
	}
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

int		handle_ld(unsigned char *m, t_proc *p)
{
	unsigned int 	var;
	unsigned int	opcode;
	unsigned char	pm[4];

	p->wait = 5;
	p->carry = 1;
	opcode = m[(p->pc + 1) % MEM_SIZE];
	p->pc = (p->pc + 2) % MEM_SIZE;
	if ((opcode & 192) >> 6 == T_IND)
	{
		pm[0] = m[p->pc];
		pm[1] = m[(p->pc + 1) % MEM_SIZE];
		parse_strtoint(&var, pm, 2);
		p->pc = (p->pc + 2) % MEM_SIZE;
	}
	else if ((opcode & 192) >> 6 == T_DIR)
	{
		pm[0] = m[p->pc];
		pm[1] = m[(p->pc + 1) % MEM_SIZE];
		pm[2] = m[(p->pc + 2) % MEM_SIZE];
		pm[3] = m[(p->pc + 3) % MEM_SIZE];
		parse_strtoint(&var, pm, 4);
		p->pc = (p->pc + 4) % MEM_SIZE;
	}
	else
	{
		p->carry = 0;
		return (0);
	}
	if ((opcode & 48) >> 4 == T_REG && m[p->pc] >= 1 && m[p->pc] <= 16)
	{
		p->regs[m[p->pc] - 1] = var;
		p->pc = (p->pc + 1) % MEM_SIZE;
	}
	else
		p->carry = 0;
	return (0);
}

int		handle_st(unsigned char *m, t_proc *p)
{
	unsigned int	opcode;
	unsigned int	op[2];

	p->wait = 5;
	opcode = m[(p->pc + 1) % MEM_SIZE];
	p->pc = (p->pc + 2) % MEM_SIZE;
	if ((opcode & 192) >> 6 == T_REG)
		op[0] = get_v_acb(opcode, m, p, 0);
	else
		return (0);
	opcode <<= 2;
	op[1] = get_v_acb(opcode, m, p, 0);
	if ((opcode & 192) >> 6 == T_REG)
		p->regs[op[1] - 1] = p->regs[op[0] - 1];
	else if ((opcode & 192) >> 6 == T_IND)
	{
		m[p->pc + op[1] % MEM_SIZE] = (unsigned char)((op[0] & 192) >> 6);
		m[(p->pc + 1) + op[1] % MEM_SIZE] = (unsigned char)((op[0] & 48) >> 4);
		m[(p->pc + 2) + op[1] % MEM_SIZE] = (unsigned char)((op[0] & 12) >> 2);
		m[(p->pc + 3) + op[1] % MEM_SIZE] = (unsigned char)(op[0] & 3);

		m[p->pc + op[1] % MEM_SIZE] = (unsigned char)((op[0] & 192) >> 6);
		m[(p->pc + 1) + op[1] % MEM_SIZE] = (unsigned char)((op[0] & 48) >> 4);
		m[(p->pc + 2) + op[1] % MEM_SIZE] = (unsigned char)((op[0] & 12) >> 2);
		m[(p->pc + 3) + op[1] % MEM_SIZE] = (unsigned char)(op[0] & 3);
	}
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

int		handle_and(unsigned char *m, t_proc *p)
{
	unsigned int 	op[3];
	unsigned int	opcode;
	int 			i;

	i = 0;
	p->wait = 6;
	p->carry = 1;
	opcode = m[(p->pc + 1) % MEM_SIZE];
	p->pc = (p->pc + 2) % MEM_SIZE;
	while (i < 3)
	{
		op[i++] = get_v_acb(opcode, m, p, 4);
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
	p->carry = 1;
	opcode = m[(p->pc + 1) % MEM_SIZE];
	p->pc = (p->pc + 2) % MEM_SIZE;
	while (i < 3)
	{
		op[i++] = get_v_acb(opcode, m, p, 4);
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
	p->carry = 1;
	opcode = m[(p->pc + 1) % MEM_SIZE];
	p->pc = (p->pc + 2) % MEM_SIZE;
	while (i < 3)
	{
		op[i++] = get_v_acb(opcode, m, p, 4);
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
	//short int		arg;
	//unsigned char	pm[2];

	p->wait = 20;
	(void)m;
	/*pm[0] = m[(p->pc + 1) % MEM_SIZE];
	pm[1] = m[(p->pc + 2) % MEM_SIZE];
	parse_strtoint(&arg, pm, 2);//test it
	if (p->carry)
	{
		p->pc = (p->pc + arg) % MEM_SIZE;
		if (p->pc < 0)
			p->pc = MEM_SIZE + p->pc;
	}*/
	p->pc = (p->pc + 3) % MEM_SIZE;
	return (0);
}

int		handle_ldi(unsigned char *m, t_proc *p)
{
	unsigned int	opcode;
	unsigned int	op[3];

	p->wait = 25;
	opcode = m[(p->pc + 1) % MEM_SIZE];
	p->pc = (p->pc + 2) % MEM_SIZE;
	if ((opcode & 192) >> 6 == T_REG || (opcode & 192) >> 6 == T_DIR ||
		(opcode & 192) >> 6 == T_IND)
	{
		op[0] = get_v_acb(opcode, m, p, 2);
		if ((opcode & 192) >> 6 == T_REG)
			op[0] = p->regs[op[0] - 1];
	}
	else
		return (0);
	opcode <<= 2;
	if ((opcode & 192) >> 6 == T_REG || (opcode & 192) >> 6 == T_DIR)
	{
		op[1] = get_v_acb(opcode, m, p, 2);
		if ((opcode & 192) >> 6 == T_REG)
			op[1] = p->regs[op[1] - 1];
	}
	else
		return (0);
	opcode <<= 2;
	if ((opcode & 192) >> 6 == T_REG)
		op[2] = get_v_acb(opcode, m, p, 0);
	else
		return (0);
	p->regs[op[2] - 1] = m[(op[0] + op[1]) % MEM_SIZE] << 6;
	p->regs[op[2] - 1] += m[(op[0] + op[1] + 1) % MEM_SIZE] << 4;
	p->regs[op[2] - 1] += m[(op[0] + op[1] + 2) % MEM_SIZE] << 2;
	p->regs[op[2] - 1] += m[(op[0] + op[1] + 3) % MEM_SIZE];
	return (0);
}

int		handle_sti(unsigned char *m, t_proc *p)
{
	unsigned int	opcode;
	unsigned int	op[3];

	p->wait = 25;
	opcode = m[(p->pc + 1) % MEM_SIZE];
	p->pc = (p->pc + 2) % MEM_SIZE;
	if ((opcode & 192) >> 6 == T_REG)
		op[0] = get_v_acb(opcode, m, p, 2);
	else
		return (0);
	opcode <<= 2;
	if ((opcode & 192) >> 6 == T_REG || (opcode & 192) >> 6 == T_DIR ||
			(opcode & 192) >> 6 == T_IND)
		op[1] = get_v_acb(opcode, m, p, 2);
	else
		return (0);
	opcode <<= 2;
	if ((opcode & 192) >> 6 == T_REG || (opcode & 192) >> 6 == T_DIR)
		op[2] = get_v_acb(opcode, m, p, 2);
	else
		return (0);
	m[(op[1] + op[2]) % MEM_SIZE] = (unsigned char)((op[0] & 192) >> 6);;
	m[(op[1] + op[2] + 1) % MEM_SIZE] = (unsigned char)((op[0] & 48) >> 4);
	m[(op[1] + op[2] + 2) % MEM_SIZE] = (unsigned char)((op[0] & 12) >> 2);
	m[(op[1] + op[2] + 3) % MEM_SIZE] = (unsigned char)(op[0] & 3);
	return (0);
}

int		handle_fork(unsigned char *m, t_proc *p, t_proc **head, t_flags *fl)
{
	unsigned int	arg;
	unsigned char	pm[2];

	pm[0] = m[(p->pc + 1) % MEM_SIZE];
	pm[1] = m[(p->pc + 2) % MEM_SIZE];
	parse_strtoint(&arg, pm, 2);		//test it
	p->wait = 800;
	add_proc(head, init_proc_data((p->pc + arg % IDX_MOD) % MEM_SIZE, p->pl, fl));
	p->pc = (p->pc + 3) % MEM_SIZE;
	return (0);
}

int		handle_lld(unsigned char *m, t_proc *p) //?? % IDX_MOD
{
	unsigned int 	var;
	unsigned int	opcode;
	unsigned char	pm[4];

	p->wait = 10;
	p->carry = 1;
	opcode = m[(p->pc + 1) % MEM_SIZE];
	p->pc = (p->pc + 2) % MEM_SIZE;
	if ((opcode & 192) >> 6 == T_IND)
	{
		pm[0] = m[p->pc];
		pm[1] = m[(p->pc + 1) % MEM_SIZE];
		parse_strtoint(&var, pm, 2);
		p->pc = (p->pc + 2) % MEM_SIZE;
	}
	else if ((opcode & 192) >> 6 == T_DIR)
	{
		pm[0] = m[p->pc];
		pm[1] = m[(p->pc + 1) % MEM_SIZE];
		pm[2] = m[(p->pc + 2) % MEM_SIZE];
		pm[3] = m[(p->pc + 3) % MEM_SIZE];
		parse_strtoint(&var, pm, 4);
		p->pc = (p->pc + 4) % MEM_SIZE;
	}
	else
	{
		p->carry = 0;
		return (0);
	}
	if ((opcode & 48) >> 4 == T_REG && m[p->pc] >= 1 && m[p->pc] <= 16)
	{
		p->regs[m[p->pc] - 1] = var;
		p->pc = (p->pc + 1) % MEM_SIZE;
	}
	else
		p->carry = 0;
	return (0);
}

int		handle_lldi(unsigned char *m, t_proc *p) //?? wtf % IDX_MOD
{
	unsigned int	opcode;
	unsigned int	op[3];

	p->wait = 50;
	opcode = m[(p->pc + 1) % MEM_SIZE];
	p->pc = (p->pc + 2) % MEM_SIZE;
	if ((opcode & 192) >> 6 == T_REG || (opcode & 192) >> 6 == T_DIR ||
		(opcode & 192) >> 6 == T_IND)
	{
		op[0] = get_v_acb(opcode, m, p, 2);
		if ((opcode & 192) >> 6 == T_REG)
			op[0] = p->regs[op[0] - 1];
	}
	else
		return (0);
	opcode <<= 2;
	if ((opcode & 192) >> 6 == T_REG || (opcode & 192) >> 6 == T_DIR)
	{
		op[1] = get_v_acb(opcode, m, p, 2);
		if ((opcode & 192) >> 6 == T_REG)
			op[1] = p->regs[op[1] - 1];
	}
	else
		return (0);
	opcode <<= 2;
	if ((opcode & 192) >> 6 == T_REG)
		op[2] = get_v_acb(opcode, m, p, 0);
	else
		return (0);
	p->regs[op[2] - 1] = m[(op[0] + op[1]) % MEM_SIZE] << 6;
	p->regs[op[2] - 1] += m[(op[0] + op[1] + 1) % MEM_SIZE] << 4;
	p->regs[op[2] - 1] += m[(op[0] + op[1] + 2) % MEM_SIZE] << 2;
	p->regs[op[2] - 1] += m[(op[0] + op[1] + 3) % MEM_SIZE];
	return (0);
}

int		handle_lfork(unsigned char *m, t_proc *p, t_proc **head, t_flags *fl)
{
	unsigned int	arg;
	unsigned char	pm[2];

	pm[0] = m[(p->pc + 1) % MEM_SIZE];
	pm[1] = m[(p->pc + 2) % MEM_SIZE];
	parse_strtoint(&arg, pm, 2);		//test it
	p->wait = 1000;
	add_proc(head, init_proc_data((p->pc + arg) % MEM_SIZE, p->pl, fl));
	p->pc = (p->pc + 3) % MEM_SIZE;
	return (0);
}

int		handle_aff(unsigned char *m, t_proc *p, t_flags fl)
{
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
