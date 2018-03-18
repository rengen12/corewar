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


//correct func behavior when acb changed. When acb incorrect - dont return smth and continue handling params

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

int		offset(unsigned char opcode, int size)
{
	int 	res;
	int 	mask;
	int 	offset;

	offset = 6;
	mask = 192;
	res = 0;
	while (size--)
	{
		if ((opcode & mask) >> offset == REG_CODE)
			res += REG_S;
		else if ((opcode & mask) >> offset == IND_CODE)
			res += IND_SIZE;
		else if ((opcode & mask) >> offset == DIR_CODE)
			res += DIR_SIZE;
		mask >>= 2;
		offset -= 2;
	}
	return (res);
}

unsigned char	get_m_v(unsigned char *m, int pc)
{
	return (m[pc % MEM_SIZE]);
}



void	proc_caret_rem(int pc)
{
	int	x;
	int y;

	x = pc % 64 * 3 + OFFSET_X;
	y = pc / 64 + OFFSET_Y;
	/*chtype temp1 = 'a';
	chtype mtemp1 = temp1 & A_ATTRIBUTES;
	chtype rtemp1 = temp1 | A_REVERSE;
	chtype rrtemp1 = temp1 | A_REVERSE;
	chtype drtemp1 = rtemp1 ^ A_REVERSE;
	if (rtemp1 == rtemp1 | A_REVERSE)
	{
		x++;
	}*/
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



















