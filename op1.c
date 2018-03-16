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
	if (opcode == REG_CODE)
	{
		res = m[p->pc];
		p->pc = (p->pc + REG_S) % MEM_SIZE;
	}
	else if (opcode == IND_CODE)
	{
		pm[0] = m[p->pc];
		pm[1] = m[(p->pc + 1) % MEM_SIZE];
		parse_strtoint(&res, pm, 2);
		p->pc = (p->pc + IND_SIZE) % MEM_SIZE;
	}
	else if (opcode == DIR_CODE)
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
	else
		p->pc = (p->pc + 1) % MEM_SIZE;
	return (res);
}

void	proc_caret_rem(int pc)
{
	int	x;
	int y;

	x = pc % 64 * 3 + OFFSET_X;
	y = pc / 64 + OFFSET_Y;
	mvaddch(y, x, mvinch(y, x) ^ A_REVERSE);
	mvaddch(y, x + 1, mvinch(y, x + 1) ^ A_REVERSE);
}

void	proc_caret_add(int pc)
{
	int	x;
	int y;

	x = pc % 64 * 3 + OFFSET_X;
	y = pc / 64 + OFFSET_Y;
	mvaddch(y, x, mvinch(y, x) | A_REVERSE);
	mvaddch(y, x + 1, mvinch(y, x + 1) | A_REVERSE);
	//initscr();
	//printw("pc = %d, x = %d, y = %d", pc, x, y);
	//refresh();
	//getch();
	//endwin();
}

int		handle_live(unsigned char *m, t_proc *p, t_player *pls)
{
	unsigned int	val;
	unsigned char	pm[4];

	p->pc_old = p->pc;
	p->pc = (p->pc + 1) % MEM_SIZE;
	pm[0] = m[p->pc];
	pm[1] = m[(p->pc + 1) % MEM_SIZE];
	pm[2] = m[(p->pc + 2) % MEM_SIZE];
	pm[3] = m[(p->pc + 3) % MEM_SIZE];
	p->cyc_to_die = CYCLE_TO_DIE;
	parse_strtoint(&val, pm, 4);
	p->pc = (p->pc + 4) % MEM_SIZE;
	return (0);
}

int		handle_ld(unsigned char *m, t_proc *p)
{
	unsigned int 	var;
	unsigned int	opcode;
	unsigned int	reg;

	opcode = m[(p->pc + 1) % MEM_SIZE];
	p->pc_old = p->pc;
	p->pc = (p->pc + 2) % MEM_SIZE;
	var = get_v_acb(opcode, m, p, 4);
	opcode <<= 2;
	reg = get_v_acb(opcode, m, p, 4);
	if ((opcode & 192) >> 6 == T_REG && reg >= 1 && reg <= 16)
		p->regs[reg - 1] = var;
	p->carry = (short)(var == 0 ? 1 : 0);
	return (0);
}

int		handle_st(unsigned char *m, t_proc *p)
{
	unsigned int	opcode;
	unsigned int	op[2];


	opcode = m[(p->pc + 1) % MEM_SIZE];
	//proc_caret_rem(p->pc);
	p->pc_old = p->pc;
	p->pc = (p->pc + 2) % MEM_SIZE;
	if ((opcode & 192) >> 6 == T_REG)
		op[0] = get_v_acb(opcode, m, p, 0);
	//else
	//	return (0);
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
//	proc_caret_add(p->pc);
	return (0);
}

int		handle_add(unsigned char *m, t_proc *p)
{

//	proc_caret_rem(p->pc);
	p->pc_old = p->pc;
	if (offset(get_m_v(m, p->pc + 1), 3) != 3  || \
		m[(p->pc + 2) % MEM_SIZE] > REG_NUMBER || \
		m[(p->pc + 2) % MEM_SIZE] < 1 || \
		m[(p->pc + 3) % MEM_SIZE] > REG_NUMBER || \
		m[(p->pc + 3) % MEM_SIZE] < 1 || \
		m[(p->pc + 4) % MEM_SIZE] > REG_NUMBER || m[(p->pc + 4) % MEM_SIZE] < 1)
	{
		p->carry = 0;
		p->pc = (p->pc + 2 + offset(get_m_v(m, p->pc + 1), 3)) % MEM_SIZE;
		//return (0);
	}
	p->regs[m[(p->pc + 4) % MEM_SIZE]] = p->regs[m[(p->pc + 2) % MEM_SIZE]] +	//sing unsign?
										 p->regs[m[(p->pc + 3) % MEM_SIZE]];
	p->pc = (p->pc + 2 + offset(get_m_v(m, p->pc + 1), 3)) % MEM_SIZE;
	p->carry = 1;
//	proc_caret_add(p->pc);
	return (0);
}

int		handle_sub(unsigned char *m, t_proc *p)
{

	p->pc_old = p->pc;
//	proc_caret_rem(p->pc);
	if (offset(get_m_v(m, p->pc + 1), 3) != 3  || \
		m[(p->pc + 2) % MEM_SIZE] > REG_NUMBER || \
		m[(p->pc + 2) % MEM_SIZE] < 1 || \
		m[(p->pc + 3) % MEM_SIZE] > REG_NUMBER || \
		m[(p->pc + 3) % MEM_SIZE] < 1 || \
		m[(p->pc + 4) % MEM_SIZE] > REG_NUMBER || m[(p->pc + 4) % MEM_SIZE] < 1)
	{
		p->carry = 0;
		p->pc = (p->pc + 2) % MEM_SIZE;
		//return (0);
	}
	p->regs[m[(p->pc + 4) % MEM_SIZE]] = p->regs[m[(p->pc + 2) % MEM_SIZE]] -	//sing unsign?
			p->regs[m[(p->pc + 3) % MEM_SIZE]];
	p->pc = (p->pc + 2 + offset(get_m_v(m, p->pc + 1), 3)) % MEM_SIZE;
	p->carry = 1;
//	proc_caret_add(p->pc);
	return (0);
}

int		handle_and(unsigned char *m, t_proc *p)
{
	unsigned int 	op[3];
	unsigned int	opcode;
	int 			i;

	i = 0;

	p->carry = 1;
	opcode = m[(p->pc + 1) % MEM_SIZE];
//	proc_caret_rem(p->pc);
	p->pc_old = p->pc;
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
		//else
		//	return (0);
	}
	if ((opcode & 48) >> 4 == T_REG && op[0] >= 1 && op[0] <= 16)
	{
		if (op[1] >= 1 && op[1] <= 16)
			op[1] = p->regs[op[1] - 1];
		//else
			//return (0);
	}
	if ((get_m_v(m, p->pc) & 12) >> 2 == REG_CODE)
		p->regs[op[2] - 1] = op[0] & op[1];
//	proc_caret_add(p->pc);
	return (0);
}

int		handle_or(unsigned char *m, t_proc *p)
{
	unsigned int 	op[3];
	unsigned int	opcode;
	int 			i;

	i = 0;

	p->carry = 1;
	opcode = m[(p->pc + 1) % MEM_SIZE];
//	proc_caret_rem(p->pc);
	p->pc_old = p->pc;
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
		//else
		//	return (0);
	}
	if ((opcode & 48) >> 4 == T_REG && op[0] >= 1 && op[0] <= 16)
	{
		if (op[1] >= 1 && op[1] <= 16)
			op[1] = p->regs[op[1] - 1];
		//else
		//	return (0);
	}
	if ((get_m_v(m, p->pc) & 12) >> 2 == REG_CODE)
		p->regs[op[2] - 1] = op[0] | op[1];
//	proc_caret_add(p->pc);
	return (0);
}

int		handle_xor(unsigned char *m, t_proc *p)
{
	unsigned int 	op[3];
	unsigned int	opcode;
	int 			i;

	i = 0;

	p->carry = 1;
	opcode = m[(p->pc + 1) % MEM_SIZE];
//	proc_caret_rem(p->pc);
	p->pc_old = p->pc;
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
		//else
		//	return (0);
	}
	if ((opcode & 48) >> 4 == T_REG)
	{
		if (op[1] >= 1 && op[1] <= 16)
			op[1] = p->regs[op[1] - 1];
		//else
		//	return (0);
	}
	if ((get_m_v(m, p->pc) & 12) >> 2 == REG_CODE)
		p->regs[op[2] - 1] = op[0] ^ op[1];
//	proc_caret_add(p->pc);
	return (0);
}

int		handle_zjmp(unsigned char *m, t_proc *p)
{
	//short int		arg;
	//unsigned char	pm[2];


	(void)m;
	p->pc_old = p->pc;
//	proc_caret_rem(p->pc);
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
//	proc_caret_add(p->pc);
	return (0);
}

int		handle_ldi(unsigned char *m, t_proc *p)
{
	unsigned int	opcode;
	unsigned int	op[3];


	opcode = m[(p->pc + 1) % MEM_SIZE];
//	proc_caret_rem(p->pc);
	p->pc_old = p->pc;
	p->pc = (p->pc + 2) % MEM_SIZE;
	if ((opcode & 192) >> 6 == T_REG || (opcode & 192) >> 6 == T_DIR ||
		(opcode & 192) >> 6 == T_IND)
	{
		op[0] = get_v_acb(opcode, m, p, 2);
		if ((opcode & 192) >> 6 == T_REG)
			op[0] = p->regs[op[0] - 1];
	}
	//else
	//	return (0);
	opcode <<= 2;
	if ((opcode & 192) >> 6 == T_REG || (opcode & 192) >> 6 == T_DIR)
	{
		op[1] = get_v_acb(opcode, m, p, 2);
		if ((opcode & 192) >> 6 == T_REG)
			op[1] = p->regs[op[1] - 1];
	}
	//else
	//	return (0);
	opcode <<= 2;
	if ((opcode & 192) >> 6 == T_REG)
		op[2] = get_v_acb(opcode, m, p, 0);
	//else
	//	return (0);
	p->regs[op[2] - 1] = m[(op[0] + op[1]) % MEM_SIZE] << 6;
	p->regs[op[2] - 1] += m[(op[0] + op[1] + 1) % MEM_SIZE] << 4;
	p->regs[op[2] - 1] += m[(op[0] + op[1] + 2) % MEM_SIZE] << 2;
	p->regs[op[2] - 1] += m[(op[0] + op[1] + 3) % MEM_SIZE];
//	proc_caret_add(p->pc);
	return (0);
}

void	get_x_y_from_mem(int *x, int *y, int pc)
{
	*x = pc % 64 * 3 + OFFSET_X;
	*y = pc / 64 + OFFSET_Y;
}

void	update_visual(unsigned char *m, unsigned int addr, t_proc *p, int size)
{
	int	x;
	int y;

	attron(COLOR_PAIR(p->pl->id));
	while (size--)
	{
		get_x_y_from_mem(&x, &y, addr % MEM_SIZE);
		move(y, x);
		pr_byte_ncurses(m[addr % MEM_SIZE], A_BOLD);
		addr = (addr + 1) % MEM_SIZE;
	}
	attroff(COLOR_PAIR(p->pl->id));


}

int		handle_sti(unsigned char *m, t_proc *p, t_flags fl)
{
	unsigned int	opcode;
	unsigned int	op[3];
	unsigned int	addr;

	p->pc_old = p->pc;
	opcode = m[(p->pc + 1) % MEM_SIZE];
	p->pc = (p->pc + 2) % MEM_SIZE;
	op[0] = get_v_acb(opcode, m, p, 2);
	if ((opcode & 192) >> 6 == REG_CODE)
		op[0] = p->regs[op[0] - 1];
	opcode <<= 2;
	op[1] = get_v_acb(opcode, m, p, 2);
	if ((opcode & 192) >> 6 == IND_CODE)
		parse_strtoint(&op[1], &m[op[1]], 4);
	if ((opcode & 192) >> 6 == REG_CODE)
		op[1] = p->regs[op[1] - 1];
	opcode <<= 2;
	op[2] = get_v_acb(opcode, m, p, 2);
	if ((opcode & 192) >> 6 == REG_CODE)
		op[2] = p->regs[op[2] - 1];
	addr = (op[1] + op[2]) % IDX_MOD;
	m[addr % MEM_SIZE] = (unsigned char)((op[0] & 4278190080) >> 24);
	m[(addr + 1) % MEM_SIZE] = (unsigned char)((op[0] & 16711680) >> 16);
	m[(addr + 2) % MEM_SIZE] = (unsigned char)((op[0] & 65280) >> 8);
	m[(addr + 3) % MEM_SIZE] = (unsigned char)(op[0] & 255);
	if (fl.v)
		update_visual(m, addr, p, 4);
	return (0);
}

int		handle_fork(unsigned char *m, t_proc *p, t_proc **head, t_flags *fl)
{
	unsigned int	arg;
	unsigned char	pm[2];

	p->pc_old = p->pc;
	pm[0] = m[(p->pc + 1) % MEM_SIZE];
	pm[1] = m[(p->pc + 2) % MEM_SIZE];
	parse_strtoint(&arg, pm, 2);		//test it

	add_proc(head, init_proc_data((p->pc + arg % IDX_MOD) % MEM_SIZE, p->pl, fl));
	proc_caret_add((*head)->pc);
	p->pc = (p->pc + 3) % MEM_SIZE;
	return (0);
}

int		handle_lld(unsigned char *m, t_proc *p) //?? % IDX_MOD
{
	unsigned int 	var;
	unsigned int	opcode;
	unsigned char	pm[4];

	var = 0;
	p->carry = 1;
	opcode = m[(p->pc + 1) % MEM_SIZE];
	p->pc_old = p->pc;
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

	if ((opcode & 48) >> 4 == T_REG && m[p->pc] >= 1 && m[p->pc] <= 16)
	{
		p->regs[m[p->pc] - 1] = var;
		p->pc = (p->pc + 1) % MEM_SIZE;
	}
	return (0);
}

int		handle_lldi(unsigned char *m, t_proc *p) //?? wtf % IDX_MOD
{
	unsigned int	opcode;
	unsigned int	op[3];


	opcode = m[(p->pc + 1) % MEM_SIZE];
//	proc_caret_rem(p->pc);
	p->pc_old = p->pc;
	p->pc = (p->pc + 2) % MEM_SIZE;
	if ((opcode & 192) >> 6 == T_REG || (opcode & 192) >> 6 == T_DIR ||
		(opcode & 192) >> 6 == T_IND)
	{
		op[0] = get_v_acb(opcode, m, p, 2);
		if ((opcode & 192) >> 6 == T_REG)
			op[0] = p->regs[op[0] - 1];
	}
	//else
	//	return (0);
	opcode <<= 2;
	if ((opcode & 192) >> 6 == T_REG || (opcode & 192) >> 6 == T_DIR)
	{
		op[1] = get_v_acb(opcode, m, p, 2);
		if ((opcode & 192) >> 6 == T_REG)
			op[1] = p->regs[op[1] - 1];
	}
	//else
	//	return (0);
	opcode <<= 2;
	if ((opcode & 192) >> 6 == T_REG)
		op[2] = get_v_acb(opcode, m, p, 0);
	//else
	//	return (0);
	p->regs[op[2] - 1] = m[(op[0] + op[1]) % MEM_SIZE] << 6;
	p->regs[op[2] - 1] += m[(op[0] + op[1] + 1) % MEM_SIZE] << 4;
	p->regs[op[2] - 1] += m[(op[0] + op[1] + 2) % MEM_SIZE] << 2;
	p->regs[op[2] - 1] += m[(op[0] + op[1] + 3) % MEM_SIZE];
//	proc_caret_add(p->pc);
	return (0);
}

int		handle_lfork(unsigned char *m, t_proc *p, t_proc **head, t_flags *fl)
{
	unsigned int	arg;
	unsigned char	pm[2];

	pm[0] = m[(p->pc + 1) % MEM_SIZE];
	pm[1] = m[(p->pc + 2) % MEM_SIZE];
	p->pc_old = p->pc;
	parse_strtoint(&arg, pm, 2);		//test it
	add_proc(head, init_proc_data((p->pc + arg) % MEM_SIZE, p->pl, fl));
	proc_caret_add((*head)->pc);
	p->pc = (p->pc + 3) % MEM_SIZE;
	return (0);
}

/*OK*/
int		handle_aff(unsigned char *m, t_proc *p, t_flags fl)
{
	int 			val;
	unsigned int	opcode;

	p->pc_old = p->pc;
	p->pc = (p->pc + 1) % MEM_SIZE;
	opcode = m[p->pc];
	val = get_v_acb(opcode, m, p, 4);
	if (opcode >> 6 == REG_CODE)
		if (fl.a && val >= 1 && val <= REG_NUMBER)
			ft_printf("%s said (aff): %c\n", p->pl->header.prog_name, \
					p->regs[val - 1] % 256);
	return (0);
}
