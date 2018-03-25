/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_ldi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amichak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 17:46:00 by amichak           #+#    #+#             */
/*   Updated: 2018/03/18 17:46:00 by amichak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../corewar.h"

static void	write_in_reg(unsigned int op2, int addr, t_proc *p,
							unsigned char *m)
{
	p->regs[op2] = m[addr] << 24;
	p->regs[op2] += m[(addr + 1) % MEM_SIZE] << 16;
	p->regs[op2] += m[(addr + 2) % MEM_SIZE] << 8;
	p->regs[op2] += m[(addr + 3) % MEM_SIZE];
}

static int	get_arg(t_proc *p, unsigned char *m, unsigned int op[3])
{
	unsigned int	opcode;
	int				ok;

	p->pc_old = p->pc;
	opcode = m[(p->pc + 1) % MEM_SIZE];
	p->pc = (p->pc + 2) % MEM_SIZE;
	ok = checkarg(opcode, T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG);
	op[0] = get_v_acb(opcode, m, p, 2);
	if (IS_REG(opcode) && IS_REGOK(op[0]))
		op[0] = p->regs[op[0] - 1];
	else if (IS_REG(opcode))
		ok--;
	else if (IS_IND(opcode))
		get_val_for_ind(&op[0], m, p, 1);
	opcode <<= 2;
	op[1] = get_v_acb(opcode, m, p, 2);
	if (IS_REG(opcode) && IS_REGOK(op[1]))
		op[1] = p->regs[op[1] - 1];
	else if (IS_REG(opcode))
		ok--;
	opcode <<= 2;
	op[2] = get_v_acb(opcode, m, p, 2);
	if (!IS_REGOK(op[2]))
		ok--;
	return (ok);
}

void		handle_ldi(unsigned char *m, t_proc *p)
{
	unsigned int	op[3];
	int				addr;
	int				ok;

	ok = get_arg(p, m, op);
	if (ok == 3)
	{
		addr = ((p->pc_old + (short)(op[0] + op[1]) % IDX_MOD) % MEM_SIZE);
		if (addr < 0)
			addr += MEM_SIZE;
		write_in_reg(--op[2], addr, p, m);
	}
}

void		handle_lldi(unsigned char *m, t_proc *p)
{
	unsigned int	op[3];
	int				addr;
	int				ok;

	ok = get_arg(p, m, op);
	if (ok == 3)
	{
		addr = (p->pc_old + (short)(op[0] + op[1])) % MEM_SIZE;
		if (addr < 0)
			addr += MEM_SIZE;
		write_in_reg(--op[2], addr, p, m);
		p->carry = (short)(p->regs[op[2]] == 0 ? 1 : 0);
	}
}
