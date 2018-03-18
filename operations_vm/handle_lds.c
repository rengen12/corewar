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

//validate incorect acb
int		handle_ld(unsigned char *m, t_proc *p)
{
	int 			var;
	unsigned int	opcode;
	unsigned int	reg;
	int 			temp;
	unsigned char	pm[4];

	p->pc_old = p->pc;
	opcode = m[(p->pc + 1) % MEM_SIZE];
	p->pc = (p->pc + 2) % MEM_SIZE;
	var = get_v_acb(opcode, m, p, 4);
	if ((opcode & 192) >> 6 == IND_CODE)
	{
		temp = ((p->pc_old + (short)var % IDX_MOD) < 0 ? MEM_SIZE +
														 (p->pc_old + (short)var % IDX_MOD) : (p->pc_old + (short)var % IDX_MOD)) % MEM_SIZE;
		pm[0] = m[temp];
		pm[1] = m[(temp + 1) % MEM_SIZE];
		pm[2] = m[(temp + 2) % MEM_SIZE];
		pm[3] = m[(temp + 3) % MEM_SIZE];
		parse_strtoint(&var, pm, 4);
	}
	opcode <<= 2;
	reg = get_v_acb(opcode, m, p, 4);
	if ((opcode & 192) >> 6 == REG_CODE && reg >= 1 && reg <= 16)
		p->regs[reg - 1] = (unsigned int)var;
	p->carry = (short)(var == 0 ? 1 : 0);
	return (0);
}

 //validate incorect acb
int		handle_lld(unsigned char *m, t_proc *p) //?? % IDX_MOD
{
	int 			var;
	unsigned int	opcode;
	unsigned int	reg;
	int 			temp;
	unsigned char	pm[4];

	p->pc_old = p->pc;
	opcode = m[(p->pc + 1) % MEM_SIZE];
	p->pc = (p->pc + 2) % MEM_SIZE;
	var = get_v_acb(opcode, m, p, 4);
	if ((opcode & 192) >> 6 == IND_CODE)
	{
		temp = ((p->pc_old + (short)var) < 0 ? MEM_SIZE +
											   (p->pc_old + (short)var) : (p->pc_old + (short)var)) % MEM_SIZE;
		pm[0] = m[temp];
		pm[1] = m[(temp + 1) % MEM_SIZE];
		pm[2] = m[(temp + 2) % MEM_SIZE];
		pm[3] = m[(temp + 3) % MEM_SIZE];
		parse_strtoint(&var, pm, 4);
	}
	opcode <<= 2;
	reg = get_v_acb(opcode, m, p, 4);
	if ((opcode & 192) >> 6 == REG_CODE && reg >= 1 && reg <= 16)
		p->regs[reg - 1] = (unsigned int)var;
	p->carry = (short)(var == 0 ? 1 : 0);
	return (0);
}