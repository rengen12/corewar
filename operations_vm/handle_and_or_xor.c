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

static void	get_val_for_ind(unsigned int *val, unsigned char *m, t_proc *p)
{
	int				addr;
	unsigned char	pm[4];

	addr = (p->pc_old + (short)*val % IDX_MOD) % MEM_SIZE;
	if (addr < 0)
		addr += MEM_SIZE;
	pm[0] = m[addr];
	pm[1] = m[(addr + 1) % MEM_SIZE];
	pm[2] = m[(addr + 2) % MEM_SIZE];
	pm[3] = m[(addr + 3) % MEM_SIZE];
	parse_strtoint(val, pm, 4);
}

void	handle_and(unsigned char *m, t_proc *p)
{
	unsigned int 	op[3];
	unsigned int	opcode;
	int 			ok;

	ok = 0;
	p->pc_old = p->pc;
	opcode = m[(p->pc + 1) % MEM_SIZE];
	p->pc = (p->pc + 2) % MEM_SIZE;
	op[0] = get_v_acb(opcode, m, p, 4);
	if ((opcode & 192) >> 6 == REG_CODE || (opcode & 192) >> 6 == IND_CODE || (opcode & 192) >> 6 == DIR_CODE)
		ok++;
	if ((opcode & 192) >> 6 == REG_CODE && op[0] >= 1 && op[0] <= REG_NUMBER)
		op[0] = p->regs[op[0] - 1];
	else if ((opcode & 192) >> 6 == IND_CODE)
		get_val_for_ind(&op[0], m, p);
	opcode <<= 2;
	op[1] = get_v_acb(opcode, m, p, 4);
	if ((opcode & 192) >> 6 == REG_CODE || (opcode & 192) >> 6 == IND_CODE || (opcode & 192) >> 6 == DIR_CODE)
		ok++;
	if ((opcode & 192) >> 6 == REG_CODE && op[1] >= 1 && op[1] <= REG_NUMBER)
		op[1] = p->regs[op[1] - 1];
	else if ((opcode & 192) >> 6 == IND_CODE)
		get_val_for_ind(&op[1], m, p);
	opcode <<= 2;
	op[2] = get_v_acb(opcode, m, p, 4);
	if ((opcode & 192) >> 6 == REG_CODE)
		ok++;
	if (ok == 3 && op[2] >= 1 && op[2] <= REG_NUMBER)
	{
		p->regs[op[2] - 1] = op[0] & op[1];
		p->carry = (short)(p->regs[op[2] - 1] == 0 ? 1 : 0);
	}
}

void	handle_or(unsigned char *m, t_proc *p)
{
	unsigned int 	op[3];
	unsigned int	opcode;
	int 			ok;

	ok = 0;
	p->pc_old = p->pc;
	opcode = m[(p->pc + 1) % MEM_SIZE];
	p->pc = (p->pc + 2) % MEM_SIZE;
	op[0] = get_v_acb(opcode, m, p, 4);
	if ((opcode & 192) >> 6 == REG_CODE || (opcode & 192) >> 6 == IND_CODE || (opcode & 192) >> 6 == DIR_CODE)
		ok++;
	if ((opcode & 192) >> 6 == REG_CODE && op[0] >= 1 && op[0] <= REG_NUMBER)
		op[0] = p->regs[op[0] - 1];
	else if ((opcode & 192) >> 6 == IND_CODE)
		get_val_for_ind(&op[0], m, p);
	opcode <<= 2;
	op[1] = get_v_acb(opcode, m, p, 4);
	if ((opcode & 192) >> 6 == REG_CODE || (opcode & 192) >> 6 == IND_CODE || (opcode & 192) >> 6 == DIR_CODE)
		ok++;
	if ((opcode & 192) >> 6 == REG_CODE && op[1] >= 1 && op[1] <= REG_NUMBER)
		op[1] = p->regs[op[1] - 1];
	else if ((opcode & 192) >> 6 == IND_CODE)
		get_val_for_ind(&op[1], m, p);
	opcode <<= 2;
	op[2] = get_v_acb(opcode, m, p, 4);
	if ((opcode & 192) >> 6 == REG_CODE)
		ok++;
	if (ok == 3 && op[2] >= 1 && op[2] <= REG_NUMBER)
	{
		p->regs[op[2] - 1] = op[0] | op[1];
		p->carry = (short)(p->regs[op[2] - 1] == 0 ? 1 : 0);
	}
}

void	handle_xor(unsigned char *m, t_proc *p)
{
	unsigned int 	op[3];
	unsigned int	opcode;
	int 			ok;

	ok = 0;
	p->pc_old = p->pc;
	opcode = m[(p->pc + 1) % MEM_SIZE];
	p->pc = (p->pc + 2) % MEM_SIZE;
	op[0] = get_v_acb(opcode, m, p, 4);
	if ((opcode & 192) >> 6 == REG_CODE || (opcode & 192) >> 6 == IND_CODE || (opcode & 192) >> 6 == DIR_CODE)
		ok++;
	if ((opcode & 192) >> 6 == REG_CODE && op[0] >= 1 && op[0] <= REG_NUMBER)
		op[0] = p->regs[op[0] - 1];
	else if ((opcode & 192) >> 6 == IND_CODE)
		get_val_for_ind(&op[0], m, p);
	opcode <<= 2;
	op[1] = get_v_acb(opcode, m, p, 4);
	if ((opcode & 192) >> 6 == REG_CODE || (opcode & 192) >> 6 == IND_CODE || (opcode & 192) >> 6 == DIR_CODE)
		ok++;
	if ((opcode & 192) >> 6 == REG_CODE && op[1] >= 1 && op[1] <= REG_NUMBER)
		op[1] = p->regs[op[1] - 1];
	else if ((opcode & 192) >> 6 == IND_CODE)
		get_val_for_ind(&op[1], m, p);
	opcode <<= 2;
	op[2] = get_v_acb(opcode, m, p, 4);
	if ((opcode & 192) >> 6 == REG_CODE)
		ok++;
	if (ok == 3 && op[2] >= 1 && op[2] <= REG_NUMBER)
	{
		p->regs[op[2] - 1] = op[0] ^ op[1];
		p->carry = (short)(p->regs[op[2] - 1] == 0 ? 1 : 0);
	}
}
