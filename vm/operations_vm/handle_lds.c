/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_lds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amichak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 17:44:00 by amichak           #+#    #+#             */
/*   Updated: 2018/03/18 17:44:00 by amichak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../corewar.h"

void		handle_ld(unsigned char *m, t_proc *p)
{
	unsigned int	opcode;
	int				ok;
	unsigned int	op[2];

	p->pc_old = p->pc;
	opcode = m[(p->pc + 1) % MEM_SIZE];
	p->pc = (p->pc + 2) % MEM_SIZE;
	ok = checkarg(opcode, T_DIR | T_IND, 0, 0);
	op[0] = get_v_acb(opcode, m, p, 4);
	if (IS_IND(opcode))
		get_val_for_ind(&op[0], m, p, 1);
	opcode <<= 2;
	op[1] = get_v_acb(opcode, m, p, 4);
	if (ok == 1 && IS_REG(opcode) && IS_REGOK(op[1]))
	{
		p->regs[op[1] - 1] = op[0];
		p->carry = (short)(op[0] == 0 ? 1 : 0);
	}
}

void		handle_lld(unsigned char *m, t_proc *p)
{
	unsigned int	opcode;
	int				ok;
	unsigned int	op[2];

	p->pc_old = p->pc;
	opcode = m[(p->pc + 1) % MEM_SIZE];
	p->pc = (p->pc + 2) % MEM_SIZE;
	ok = checkarg(opcode, T_DIR | T_IND, 0, 0);
	op[0] = get_v_acb(opcode, m, p, 4);
	if (IS_IND(opcode))
		get_val_for_ind(&op[0], m, p, 0);
	opcode <<= 2;
	op[1] = get_v_acb(opcode, m, p, 4);
	if (ok == 1 && IS_REG(opcode) && IS_REGOK(op[1]))
	{
		p->regs[op[1] - 1] = op[0];
		p->carry = (short)(op[0] == 0 ? 1 : 0);
	}
}
