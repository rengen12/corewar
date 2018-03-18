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

 //validate incorect acb
int		handle_add(unsigned char *m, t_proc *p)
{
	unsigned int	op[3];
	unsigned int	opcode;

	p->pc_old = p->pc;
	opcode = m[(p->pc + 1) % MEM_SIZE];
	p->pc = (p->pc + 2) % MEM_SIZE;
	op[0] = get_v_acb(opcode, m, p, 4);
	opcode <<= 2;
	op[1] = get_v_acb(opcode, m, p, 4);
	opcode <<= 2;
	op[2] = get_v_acb(opcode, m, p, 4);
	if (op[0] <= REG_NUMBER && op[0] >= 1 && op[1] <= REG_NUMBER && op[1] >= 1 \
		&& op[2] <= REG_NUMBER && op[2] >= 1)
		p->regs[--op[2]] = p->regs[--op[0]] + p->regs[--op[1]]; //test overflow
	p->carry = (short)(op[2] == 0 ? 1 : 0);
	return (0);
}

 //validate incorect acb
int		handle_sub(unsigned char *m, t_proc *p)
{
	unsigned int	op[3];
	unsigned int	opcode;

	p->pc_old = p->pc;
	opcode = m[(p->pc + 1) % MEM_SIZE];
	p->pc = (p->pc + 2) % MEM_SIZE;
	op[0] = get_v_acb(opcode, m, p, 4);
	opcode <<= 2;
	op[1] = get_v_acb(opcode, m, p, 4);
	opcode <<= 2;
	op[2] = get_v_acb(opcode, m, p, 4);
	if (op[0] <= REG_NUMBER && op[0] >= 1 && op[1] <= REG_NUMBER && op[1] >= 1 \
		&& op[2] <= REG_NUMBER && op[2] >= 1)
		p->regs[--op[2]] = p->regs[--op[0]] - p->regs[--op[1]]; //test overflow
	p->carry = (short)(op[2] == 0 ? 1 : 0);
	return (0);
}
