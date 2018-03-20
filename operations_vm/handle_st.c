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

/*verif*/
int		handle_st(unsigned char *m, t_proc *p, t_flags fl)
{
	unsigned int	opcode;
	unsigned int	op[2];
	int				addr;
	int 			ok;

	ok = 0;
	p->pc_old = p->pc;
	opcode = m[(p->pc + 1) % MEM_SIZE];
	p->pc = (p->pc + 2) % MEM_SIZE;
	op[0] = get_v_acb(opcode, m, p, 4);
	if ((opcode & 192) >> 6 == REG_CODE && op[0] >= 1 && op[0] <= REG_NUMBER)
	{
		op[0] = p->regs[op[0] - 1];
		ok++;
	}
	opcode <<= 2;
	op[1] = get_v_acb(opcode, m, p, 4);
	/*temp = (p->pc_old + op[1] % IDX_MOD) % MEM_SIZE;
	pm[0] = m[temp];
	pm[1] = m[(temp + 1) % MEM_SIZE];
	pm[2] = m[(temp + 2) % MEM_SIZE];
	pm[3] = m[(temp + 3) % MEM_SIZE];
	parse_strtoint(&op[1], pm, 4);*/
	if (ok == 1 && (opcode & 192) >> 6 == REG_CODE && op[1] >= 1 && op[1] <= REG_NUMBER)
		p->regs[op[1] - 1] = op[0];
	else if (ok == 1 && (opcode & 192) >> 6 == IND_CODE)
	{
		//addr = ((p->pc_old + op[1] % IDX_MOD) % MEM_SIZE) /*% IDX_MOD*/; //???????
		addr = ((p->pc_old + op[1] % IDX_MOD) % MEM_SIZE) /*% IDX_MOD*/; //???????
		if (p->pc_old + op[1] > 32535)
			addr = MEM_SIZE + (op[1] % IDX_MOD + p->pc_old) - IDX_MOD;
		m[addr] = (unsigned char)((op[0] & 4278190080) >> 24);
		m[(addr + 1) % MEM_SIZE] = (unsigned char)((op[0] & 16711680) >> 16);
		m[(addr + 2) % MEM_SIZE] = (unsigned char)((op[0] & 65280) >> 8);
		m[(addr + 3) % MEM_SIZE] = (unsigned char)(op[0] & 255);
		if (fl.v)
			update_visual(m, (unsigned int)addr, p, 4);
	}
	return (0);
}