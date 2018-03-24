/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_add_sub.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amichak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 17:45:00 by amichak           #+#    #+#             */
/*   Updated: 2018/03/18 17:45:00 by amichak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../corewar.h"

void	handle_add(unsigned char *m, t_proc *p)
{
	unsigned int	op[3];
	unsigned int	opcode;
	int				ok;

	p->pc_old = p->pc;
	opcode = m[(p->pc + 1) % MEM_SIZE];
	p->pc = (p->pc + 2) % MEM_SIZE;
	ok = checkarg(opcode, T_REG, T_REG, T_REG);
	op[0] = get_v_acb(opcode, m, p, 4);
	opcode <<= 2;
	op[1] = get_v_acb(opcode, m, p, 4);
	opcode <<= 2;
	op[2] = get_v_acb(opcode, m, p, 4);
	if (ok == 3 && IS_REGOK(op[0]) && IS_REGOK(op[1]) && IS_REGOK(op[2]))
	{
		p->regs[--op[2]] = p->regs[--op[0]] + p->regs[--op[1]];
		p->carry = (short)(p->regs[op[2]] == 0 ? 1 : 0);
	}
}

void	handle_sub(unsigned char *m, t_proc *p)
{
	unsigned int	op[3];
	unsigned int	opcode;
	int				ok;

	p->pc_old = p->pc;
	opcode = m[(p->pc + 1) % MEM_SIZE];
	p->pc = (p->pc + 2) % MEM_SIZE;
	ok = checkarg(opcode, T_REG, T_REG, T_REG);
	op[0] = get_v_acb(opcode, m, p, 4);
	opcode <<= 2;
	op[1] = get_v_acb(opcode, m, p, 4);
	opcode <<= 2;
	op[2] = get_v_acb(opcode, m, p, 4);
	if (ok == 3 && IS_REGOK(op[0]) && IS_REGOK(op[1]) && IS_REGOK(op[2]))
	{
		p->regs[--op[2]] = p->regs[--op[0]] - p->regs[--op[1]];
		p->carry = (short)(p->regs[op[2]] == 0 ? 1 : 0);
	}
}
