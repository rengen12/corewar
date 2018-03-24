/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amichak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 17:56:00 by amichak           #+#    #+#             */
/*   Updated: 2018/03/18 17:56:00 by amichak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../corewar.h"

int				checkarg(unsigned int opcode, int arg1, int arg2, int arg3)
{
	int		res;

	res = 0;
	if (GET2B(opcode) & arg1)
	{
		res++;
		opcode <<= 2;
		if (arg2 > 0 && GET2B(opcode) & arg2)
		{
			res++;
			opcode <<= 2;
			if (arg3 > 0 && GET2B(opcode) & arg3)
				res++;
		}
	}
	return (res);
}

static void		for_dir4(unsigned char *pm, t_proc *p, unsigned char *m,
							int dir_size)
{
	if (dir_size > 2)
	{
		pm[2] = m[(p->pc + 2) % MEM_SIZE];
		pm[3] = m[(p->pc + 3) % MEM_SIZE];
	}
}

unsigned int	get_v_acb(unsigned int opcode, unsigned char *m, t_proc *p,
							int dir_size)
{
	unsigned char	pm[4];
	unsigned int	res;

	opcode = (opcode & 192) >> 6;
	if ((res = 0) == 0 && opcode == REG_CODE)
	{
		res = m[p->pc];
		p->pc = (p->pc + REG_S) % MEM_SIZE;
	}
	else if (opcode == IND_CODE)
	{
		pm[0] = m[p->pc];
		pm[1] = m[(p->pc + 1) % MEM_SIZE];
		parse_strtoint(&res, pm, 2);
		p->pc = (p->pc + IND_SIZE) % MEM_SIZE;
	}
	else if (opcode == DIR_CODE)
	{
		pm[0] = m[p->pc];
		pm[1] = m[(p->pc + 1) % MEM_SIZE];
		for_dir4(pm, p, m, dir_size);
		parse_strtoint(&res, pm, dir_size);
		p->pc = (p->pc + dir_size) % MEM_SIZE;
	}
	return (res);
}

void			get_val_for_ind(unsigned int *val, unsigned char *m, t_proc *p,
								int idx)
{
	int				addr;
	unsigned char	pm[4];

	if (idx)
		addr = (p->pc_old + (short)*val % IDX_MOD) % MEM_SIZE;
	else
		addr = (p->pc_old + (short)*val) % MEM_SIZE;
	if (addr < 0)
		addr += MEM_SIZE;
	pm[0] = m[addr];
	pm[1] = m[(addr + 1) % MEM_SIZE];
	pm[2] = m[(addr + 2) % MEM_SIZE];
	pm[3] = m[(addr + 3) % MEM_SIZE];
	parse_strtoint(val, pm, 4);
}

void			set_val_for_mem(unsigned char *m, unsigned int op0, int addr)
{
	m[addr] = (unsigned char)((op0 & 4278190080) >> 24);
	m[(addr + 1) % MEM_SIZE] = (unsigned char)((op0 & 16711680) >> 16);
	m[(addr + 2) % MEM_SIZE] = (unsigned char)((op0 & 65280) >> 8);
	m[(addr + 3) % MEM_SIZE] = (unsigned char)(op0 & 255);
}
