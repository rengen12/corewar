/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_and_or_xor.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amichak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 17:45:00 by amichak           #+#    #+#             */
/*   Updated: 2018/03/18 17:45:00 by amichak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../corewar.h"


 //validate incorect acb
int		handle_and(unsigned char *m, t_proc *p)
{
	unsigned int 	op[3];
	unsigned int	opcode;
	unsigned char	pm[4];
	unsigned int	temp;
	int 			ok;

	ok = 0;
	p->pc_old = p->pc;
	opcode = m[(p->pc + 1) % MEM_SIZE];
	p->pc = (p->pc + 2) % MEM_SIZE;
	op[0] = get_v_acb(opcode, m, p, 4);
	if ((opcode & 192) >> 6 == REG_CODE || (opcode & 192) >> 6 == IND_CODE || (opcode & 192) >> 6 == DIR_CODE)
		ok++;
	if ((opcode & 192) >> 6 == REG_CODE && op[0] >= 1 && op[0] <= REG_NUMBER) //handle res of incorrect reg
		op[0] = p->regs[op[0] - 1];
	else if ((opcode & 192) >> 6 == IND_CODE)
	{
		//temp = ((p->pc_old + (short)op[0]) < 0 ? MEM_SIZE + (p->pc_old + \
		//		(short)op[0]) : (p->pc_old + (short)op[0] % IDX_MOD)) % MEM_SIZE;
		temp = (p->pc_old + op[0] % IDX_MOD) % MEM_SIZE;
		if ((short)p->pc_old + op[0] > 32767)
			temp = MEM_SIZE + (op[0] % IDX_MOD + p->pc_old) - IDX_MOD;
		pm[0] = m[temp];
		pm[1] = m[(temp + 1) % MEM_SIZE];
		pm[2] = m[(temp + 2) % MEM_SIZE];
		pm[3] = m[(temp + 3) % MEM_SIZE];
		parse_strtoint(&op[0], pm, 4);
	}
	opcode <<= 2;
	op[1] = get_v_acb(opcode, m, p, 4);
	if ((opcode & 192) >> 6 == REG_CODE || (opcode & 192) >> 6 == IND_CODE || (opcode & 192) >> 6 == DIR_CODE)
		ok++;
	if ((opcode & 192) >> 6 == REG_CODE && op[1] >= 1 && op[1] <= REG_NUMBER) //handle res of incorrect reg num
		op[1] = p->regs[op[1] - 1];
	else if ((opcode & 192) >> 6 == IND_CODE)
	{
		//temp = ((p->pc_old + (short)op[1]) < 0 ? MEM_SIZE + (p->pc_old + \
		//		(short)op[1]) : (p->pc_old + (short)op[1] % IDX_MOD)) % MEM_SIZE;
		temp = (p->pc_old + op[1] % IDX_MOD) % MEM_SIZE;
		if ((short)p->pc_old + op[1] > 32767)
			temp = MEM_SIZE + (op[1] % IDX_MOD + p->pc_old) - IDX_MOD;
		pm[0] = m[temp];
		pm[1] = m[(temp + 1) % MEM_SIZE];
		pm[2] = m[(temp + 2) % MEM_SIZE];
		pm[3] = m[(temp + 3) % MEM_SIZE];
		parse_strtoint(&op[1], pm, 4);
	}
	opcode <<= 2;
	op[2] = get_v_acb(opcode, m, p, 4);
	if ((opcode & 192) >> 6 == REG_CODE)
		ok++;
	if (ok == 3 && op[2] >= 1 && op[2] <= REG_NUMBER)
	{
		p->regs[op[2] - 1] = op[0] & op[1];
		p->carry = (short)(p->regs[op[2] - 1] == 0 ? 1 : 0);
	}
	return (0);
}

//validate incorect acb
int		handle_or(unsigned char *m, t_proc *p)
{
	unsigned int 	op[3];
	unsigned int	opcode;
	unsigned char	pm[4];
	unsigned int	temp;
	int 			ok;

	ok = 0;
	p->pc_old = p->pc;
	opcode = m[(p->pc + 1) % MEM_SIZE];
	p->pc = (p->pc + 2) % MEM_SIZE;
	op[0] = get_v_acb(opcode, m, p, 4);
	if ((opcode & 192) >> 6 == REG_CODE || (opcode & 192) >> 6 == IND_CODE || (opcode & 192) >> 6 == DIR_CODE)
		ok++;
	if ((opcode & 192) >> 6 == REG_CODE && op[0] >= 1 && op[0] <= REG_NUMBER) //handle res of incorrect reg
		op[0] = p->regs[op[0] - 1];
	else if ((opcode & 192) >> 6 == IND_CODE)
	{
		//temp = ((p->pc_old + (short)op[0]) < 0 ? MEM_SIZE + (p->pc_old + \
		//		(short)op[0]) : (p->pc_old + (short)op[0])) % MEM_SIZE;
		temp = (p->pc_old + op[0] % IDX_MOD) % MEM_SIZE;
		if ((short)p->pc_old + op[0] > 32767)
			temp = MEM_SIZE + (op[0] % IDX_MOD + p->pc_old) - IDX_MOD;
		pm[0] = m[temp];
		pm[1] = m[(temp + 1) % MEM_SIZE];
		pm[2] = m[(temp + 2) % MEM_SIZE];
		pm[3] = m[(temp + 3) % MEM_SIZE];
		parse_strtoint(&op[0], pm, 4);
	}
	opcode <<= 2;
	op[1] = get_v_acb(opcode, m, p, 4);
	if ((opcode & 192) >> 6 == REG_CODE || (opcode & 192) >> 6 == IND_CODE || (opcode & 192) >> 6 == DIR_CODE)
		ok++;
	if ((opcode & 192) >> 6 == REG_CODE && op[1] >= 1 && op[1] <= REG_NUMBER) //handle res of incorrect reg num
		op[1] = p->regs[op[1] - 1];
	else if ((opcode & 192) >> 6 == IND_CODE)
	{
		//temp = ((p->pc_old + (short)op[1]) < 0 ? MEM_SIZE + (p->pc_old + \
		//		(short)op[1]) : (p->pc_old + (short)op[1])) % MEM_SIZE;
		temp = (p->pc_old + op[1] % IDX_MOD) % MEM_SIZE;
		if ((short)p->pc_old + op[1] > 32767)
			temp = MEM_SIZE + (op[1] % IDX_MOD + p->pc_old) - IDX_MOD;
		pm[0] = m[temp];
		pm[1] = m[(temp + 1) % MEM_SIZE];
		pm[2] = m[(temp + 2) % MEM_SIZE];
		pm[3] = m[(temp + 3) % MEM_SIZE];
		parse_strtoint(&op[1], pm, 4);
	}
	opcode <<= 2;
	op[2] = get_v_acb(opcode, m, p, 4);
	if ((opcode & 192) >> 6 == REG_CODE)
		ok++;
	if (ok == 3 && op[2] >= 1 && op[2] <= REG_NUMBER)
	{
		p->regs[op[2] - 1] = op[0] | op[1];
		p->carry = (short)(p->regs[op[2] - 1] == 0 ? 1 : 0);
	}
	return (0);
}

 //validate incorect acb
int		handle_xor(unsigned char *m, t_proc *p)
{
	unsigned int 	op[3];
	unsigned int	opcode;
	unsigned char	pm[4];
	unsigned int	temp;
	int 			ok;

	ok = 0;
	p->pc_old = p->pc;
	opcode = m[(p->pc + 1) % MEM_SIZE];
	p->pc = (p->pc + 2) % MEM_SIZE;
	op[0] = get_v_acb(opcode, m, p, 4);
	if ((opcode & 192) >> 6 == REG_CODE || (opcode & 192) >> 6 == IND_CODE || (opcode & 192) >> 6 == DIR_CODE)
		ok++;
	if ((opcode & 192) >> 6 == REG_CODE && op[0] >= 1 && op[0] <= REG_NUMBER) //handle res of incorrect reg
		op[0] = p->regs[op[0] - 1];
	else if ((opcode & 192) >> 6 == IND_CODE)
	{
		//temp = ((p->pc_old + (short)op[0]) < 0 ? MEM_SIZE + (p->pc_old + \
		//		(short)op[0]) : (p->pc_old + (short)op[0])) % MEM_SIZE;
		temp = (p->pc_old + op[0] % IDX_MOD) % MEM_SIZE;
		if ((short)p->pc_old + op[0] > 32767)
			temp = MEM_SIZE + (op[0] % IDX_MOD + p->pc_old) - IDX_MOD;
		pm[0] = m[temp];
		pm[1] = m[(temp + 1) % MEM_SIZE];
		pm[2] = m[(temp + 2) % MEM_SIZE];
		pm[3] = m[(temp + 3) % MEM_SIZE];
		parse_strtoint(&op[0], pm, 4);
	}
	opcode <<= 2;
	op[1] = get_v_acb(opcode, m, p, 4);
	if ((opcode & 192) >> 6 == REG_CODE || (opcode & 192) >> 6 == IND_CODE || (opcode & 192) >> 6 == DIR_CODE)
		ok++;
	if ((opcode & 192) >> 6 == REG_CODE && op[1] >= 1 && op[1] <= REG_NUMBER) //handle res of incorrect reg num
		op[1] = p->regs[op[1] - 1];
	else if ((opcode & 192) >> 6 == IND_CODE)
	{
		//temp = ((p->pc_old + (short)op[1]) < 0 ? MEM_SIZE + (p->pc_old + \
		//		(short)op[1]) : (p->pc_old + (short)op[1])) % MEM_SIZE;
		temp = (p->pc_old + op[1] % IDX_MOD) % MEM_SIZE;
		if ((short)p->pc_old + op[1] > 32767)
			temp = MEM_SIZE + (op[1] % IDX_MOD + p->pc_old) - IDX_MOD;
		pm[0] = m[temp];
		pm[1] = m[(temp + 1) % MEM_SIZE];
		pm[2] = m[(temp + 2) % MEM_SIZE];
		pm[3] = m[(temp + 3) % MEM_SIZE];
		parse_strtoint(&op[1], pm, 4);
	}
	opcode <<= 2;
	op[2] = get_v_acb(opcode, m, p, 4);
	if ((opcode & 192) >> 6 == REG_CODE)
		ok++;
	if (ok == 3 && op[2] >= 1 && op[2] <= REG_NUMBER)
	{
		p->regs[op[2] - 1] = op[0] ^ op[1];
		p->carry = (short)(p->regs[op[2] - 1] == 0 ? 1 : 0);
	}
	return (0);
}
