/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_waiting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amichak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/24 14:48:00 by amichak           #+#    #+#             */
/*   Updated: 2018/03/24 14:48:00 by amichak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	set_waiting1(t_proc *p)
{
	if (STI == p->to_ex)
		p->wait = 25;
	else if (FORK == p->to_ex)
		p->wait = 800;
	else if (LLD == p->to_ex)
		p->wait = 10;
	else if (LLDI == p->to_ex)
		p->wait = 50;
	else if (LFORK == p->to_ex)
		p->wait = 1000;
	else if (AFF == p->to_ex)
		p->wait = 2;
}

void		set_waiting(unsigned char *m, t_proc *p)
{
	p->to_ex = m[p->pc];
	if (LIVE == p->to_ex)
		p->wait = 10;
	else if (LD == p->to_ex)
		p->wait = 5;
	else if (ST == p->to_ex)
		p->wait = 5;
	else if (ADD == p->to_ex)
		p->wait = 10;
	else if (SUB == p->to_ex)
		p->wait = 10;
	else if (AND == p->to_ex)
		p->wait = 6;
	else if (OR == p->to_ex)
		p->wait = 6;
	else if (XOR == p->to_ex)
		p->wait = 6;
	else if (ZJMP == p->to_ex)
		p->wait = 20;
	else if (LDI == p->to_ex)
		p->wait = 25;
	else if (STI == p->to_ex || FORK == p->to_ex || LLD == p->to_ex ||
				LLDI == p->to_ex || LFORK == p->to_ex || AFF == p->to_ex)
		set_waiting1(p);
}
