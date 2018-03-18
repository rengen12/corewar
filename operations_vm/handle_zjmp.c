/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_zjmp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amichak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 17:46:00 by amichak           #+#    #+#             */
/*   Updated: 2018/03/18 17:46:00 by amichak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../corewar.h"


int		handle_zjmp(unsigned char *m, t_proc *p)
{
	unsigned int	arg;
	unsigned char	pm[2];

	p->pc_old = p->pc;
	pm[0] = m[(p->pc + 1) % MEM_SIZE];
	pm[1] = m[(p->pc + 2) % MEM_SIZE];
	parse_strtoint(&arg, pm, 2);//test it
	if (p->carry)
	{
		p->pc = (p->pc_old + arg) % MEM_SIZE;
		if (p->pc < 0)
			p->pc = MEM_SIZE + p->pc;
	}
	else
		p->pc = (p->pc_old + 3) % MEM_SIZE;
	return (0);
}
