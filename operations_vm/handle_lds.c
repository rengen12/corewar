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


/*verif*/
void		handle_ld(unsigned char *m, t_proc *p)
{
	int 			val;
	unsigned int	opcode;
	unsigned int	reg;
	int 			temp;
	unsigned char	pm[4];
	int 			ok;

	ok = 0;
	p->pc_old = p->pc;
	opcode = m[(p->pc + 1) % MEM_SIZE];
	p->pc = (p->pc + 2) % MEM_SIZE;
	val = get_v_acb(opcode, m, p, 4);
	if ((opcode & 192) >> 6 == IND_CODE || (opcode & 192) >> 6 == DIR_CODE)
		ok++;
	if ((opcode & 192) >> 6 == IND_CODE)
	{
		//temp = ((p->pc_old + (short)val % IDX_MOD) < 0 ? MEM_SIZE +
		//												 (p->pc_old + (short)val % IDX_MOD) : (p->pc_old + (short)val % IDX_MOD)) % MEM_SIZE;
		//temp = ((p->pc_old + val ) % MEM_SIZE) % IDX_MOD;//
		temp = ((p->pc_old + (short)val % IDX_MOD) % MEM_SIZE) ;//
		if (temp < 0)
			temp += MEM_SIZE;
		pm[0] = m[temp];
		pm[1] = m[(temp + 1) % MEM_SIZE];
		pm[2] = m[(temp + 2) % MEM_SIZE];
		pm[3] = m[(temp + 3) % MEM_SIZE];
		parse_strtoint(&val, pm, 4);
	}
	opcode <<= 2;
	reg = get_v_acb(opcode, m, p, 4);
	if (ok == 1 && (opcode & 192) >> 6 == REG_CODE && reg >= 1 && reg <= REG_NUMBER)
	{
		p->regs[reg - 1] = (unsigned int)val;
		p->carry = (short)(val == 0 ? 1 : 0);
	}
}

/*verif*/
void		handle_lld(unsigned char *m, t_proc *p) //?? % IDX_MOD
{
	unsigned int 	val;
	unsigned int	opcode;
	unsigned int	reg;
	int 	temp;
	unsigned char	pm[4];
	int 			ok;

	ok = 0;
	p->pc_old = p->pc;
	opcode = m[(p->pc + 1) % MEM_SIZE];
	p->pc = (p->pc + 2) % MEM_SIZE;
	val = get_v_acb(opcode, m, p, 4);
	if ((opcode & 192) >> 6 == IND_CODE || (opcode & 192) >> 6 == DIR_CODE)
		ok++;
	if ((opcode & 192) >> 6 == IND_CODE)
	{
		//temp = ((p->pc_old + (short)val) < 0 ? MEM_SIZE +
		//									   (p->pc_old + (short)val) : (p->pc_old + (short)val)) % MEM_SIZE;
		temp = (p->pc_old + (short)val) % MEM_SIZE;
		if (temp < 0)
			temp += MEM_SIZE;
		pm[0] = m[temp];
		pm[1] = m[(temp + 1) % MEM_SIZE];
		pm[2] = m[(temp + 2) % MEM_SIZE];
		pm[3] = m[(temp + 3) % MEM_SIZE];
		parse_strtoint(&val, pm, 4);
	}
	opcode <<= 2;
	reg = get_v_acb(opcode, m, p, 4);
	if (ok == 1 && (opcode & 192) >> 6 == REG_CODE && reg >= 1 && reg <= REG_NUMBER)
	{
		p->regs[reg - 1] = val;
		p->carry = (short)(val == 0 ? 1 : 0);
	}
}