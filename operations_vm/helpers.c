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

static void		for_dir4(unsigned char *pm, t_proc *p, unsigned char *m,
							int dir_size)
{
	if (dir_size > 2)
	{
		pm[2] = m[(p->pc + 2) % MEM_SIZE];
		pm[3] = m[(p->pc + 3) % MEM_SIZE];
	}
}

/*verif*/
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
