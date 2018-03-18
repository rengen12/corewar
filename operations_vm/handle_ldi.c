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

//validate incorect acb
int		handle_ldi(unsigned char *m, t_proc *p)
{
	unsigned int	opcode;
	unsigned int	op[3];
	int				addr;
	unsigned char	pm[4];
	int				temp;

	p->pc_old = p->pc;
	opcode = m[(p->pc + 1) % MEM_SIZE];
	p->pc = (p->pc + 2) % MEM_SIZE;
	op[0] = get_v_acb(opcode, m, p, 2);
	if ((opcode & 192) >> 6 == REG_CODE)
		op[0] = p->regs[op[0] - 1];
	else if ((opcode & 192) >> 6 == IND_CODE)
	{
		temp = ((p->pc_old + (short)op[0]) < 0 ? MEM_SIZE + (p->pc_old + \
				(short)op[0]) : (p->pc_old + (short)op[0])) % MEM_SIZE;
		pm[0] = m[temp];
		pm[1] = m[(temp + 1) % MEM_SIZE];
		pm[2] = m[(temp + 2) % MEM_SIZE];
		pm[3] = m[(temp + 3) % MEM_SIZE];
		parse_strtoint(&op[0], pm, 4);
	}
	opcode <<= 2;
	op[1] = get_v_acb(opcode, m, p, 2);
	if ((opcode & 192) >> 6 == REG_CODE)
		op[1] = p->regs[op[1] - 1];
	opcode <<= 2;
	op[2] = get_v_acb(opcode, m, p, 2);
	int lol = op[0] + (int)op[1];
	addr = (p->pc_old + (lol) % IDX_MOD) % MEM_SIZE; //не надо шорт к оп 0 птомш оно размером 4 (если регистр дать??)
	if (addr < 0)
		addr = MEM_SIZE + addr;
	if (op[2] >= 1 && op[2] <= REG_NUMBER)
	{
		p->regs[--op[2]] = m[addr] << 24;
		p->regs[op[2]] += m[(addr + 1) % MEM_SIZE] << 16;
		p->regs[op[2]] += m[(addr + 2) % MEM_SIZE] << 8;
		p->regs[op[2]] += m[(addr + 3) % MEM_SIZE];
	}
	return (0);
}