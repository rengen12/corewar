/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_st.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amichak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 17:44:00 by amichak           #+#    #+#             */
/*   Updated: 2018/03/18 17:44:00 by amichak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../corewar.h"

void		set_val_for_mem(unsigned char *m, unsigned int op0, int addr)
{
	m[addr] = (unsigned char)((op0 & 4278190080) >> 24);
	m[(addr + 1) % MEM_SIZE] = (unsigned char)((op0 & 16711680) >> 16);
	m[(addr + 2) % MEM_SIZE] = (unsigned char)((op0 & 65280) >> 8);
	m[(addr + 3) % MEM_SIZE] = (unsigned char)(op0 & 255);
}

void		handle_st(unsigned char *m, t_proc *p, t_flags fl)
{
	unsigned int	opcode;
	unsigned int	op[2];
	int				addr;
	int 			ok;

	p->pc_old = p->pc;
	opcode = m[(p->pc + 1) % MEM_SIZE];
	p->pc = (p->pc + 2) % MEM_SIZE;
	ok = checkarg(opcode, T_REG, 0, 0);
	op[0] = get_v_acb(opcode, m, p, 4);
	if (IS_REG(opcode & 192) && IS_REGOK(op[0])) //when reg isn ok
		op[0] = p->regs[op[0] - 1];
	opcode <<= 2;
	op[1] = get_v_acb(opcode, m, p, 4);
	if (ok == 1 && IS_REG(opcode) && IS_REGOK(op[1]))
		p->regs[op[1] - 1] = op[0];
	else if (ok == 1 && IS_IND(opcode))
	{
		addr = ((p->pc_old + (short)op[1] % IDX_MOD) % MEM_SIZE);
		if (addr < 0)
			addr = MEM_SIZE + addr;
		set_val_for_mem(m, op[0], addr);
		if (fl.v)
			update_visual(m, (unsigned int)addr, p, 4);
	}
}