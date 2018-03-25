/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_aff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amichak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 17:37:00 by amichak           #+#    #+#             */
/*   Updated: 2018/03/18 17:37:00 by amichak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../corewar.h"

void	handle_aff(unsigned char *m, t_proc *p, t_flags fl)
{
	int				val;
	unsigned int	opcode;

	p->pc_old = p->pc;
	opcode = m[(p->pc + 1) % MEM_SIZE];
	p->pc = (p->pc + 2) % MEM_SIZE;
	val = get_v_acb(opcode, m, p, 4);
	if (IS_REG(opcode))
		if (fl.a && !fl.v && IS_REGOK(val))
			ft_printf("%s said (aff): %c\n", p->pl->header.prog_name, \
					p->regs[val - 1] % 256);
}
