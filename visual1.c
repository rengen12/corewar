/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op1.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amichak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 14:41:00 by amichak           #+#    #+#             */
/*   Updated: 2018/03/07 14:41:00 by amichak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	get_x_y_from_mem(int *x, int *y, int pc)
{
	*x = pc % 64 * 3 + OFFSET_X;
	*y = pc / 64 + OFFSET_Y;
}

void	update_visual(unsigned char *m, unsigned int addr, t_proc *p, int size)
{
	int	x;
	int y;

	attron(COLOR_PAIR(p->pl->id));
	while (size--)
	{
		get_x_y_from_mem(&x, &y, addr % MEM_SIZE);
		move(y, x);
		pr_byte_ncurses(m[addr % MEM_SIZE], A_BOLD);
		addr = (addr + 1) % MEM_SIZE;
	}
	attroff(COLOR_PAIR(p->pl->id));
}

void	proc_caret_rem(int pc)
{
	int	x;
	int y;

	x = pc % 64 * 3 + OFFSET_X;
	y = pc / 64 + OFFSET_Y;
	if ((mvinch(y, x) | A_REVERSE) == mvinch(y, x))
		mvaddch(y, x, mvinch(y, x) ^ A_REVERSE);
	if ((mvinch(y, x + 1) | A_REVERSE) == mvinch(y, x + 1))
		mvaddch(y, x + 1, mvinch(y, x + 1) ^ A_REVERSE);
}

void	proc_caret_add(int pc)
{
	int	x;
	int y;

	x = pc % 64 * 3 + OFFSET_X;
	y = pc / 64 + OFFSET_Y;
	mvaddch(y, x, mvinch(y, x) | A_REVERSE);
	mvaddch(y, x + 1, mvinch(y, x + 1) | A_REVERSE);
}
