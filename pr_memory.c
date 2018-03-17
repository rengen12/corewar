/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pr_memory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amichak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 19:32:00 by amichak           #+#    #+#             */
/*   Updated: 2018/03/06 19:32:00 by amichak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	pr_byte(unsigned char n)
{
	ft_putchar("0123456789abcdef"[n / 16]);
	ft_putchar("0123456789abcdef"[n % 16]);

}

void	print_mem(unsigned char *m)
{
	int 	i;

	i = 0;
	while (i < MEM_SIZE)
	{
		pr_byte(m[i++]);
		ft_putchar(' ');
		if ((i % 64) == 0)
			ft_putchar('\n');
	}
}

void	pr_byte_ncurses(unsigned int n, unsigned int new)
{
	addch((chtype)"0123456789abcdef"[(n) / 16] | new);
	addch((chtype)"0123456789abcdef"[(n) % 16] | new);

}
void	print_addr()
{
	int		i;

	i = 0;
	while (i / 3 < 64)
	{
		move(2, i + OFFSET_X);
		printw("%.2d ", i / 3);
		i += 3;
	}
	i = 0;
	while (i < 64)
	{
		move(i + OFFSET_Y, 2);
		printw("%0.2d: ", i++);
	}
}

void	print_frame()
{
	int 	i;

	i = 0;
	attron(COLOR_PAIR(FRAME));
	mvprintw(0, 0, "%253c", ' ');
	while (i < 68)
	{
		mvaddch(i, 0, ' ');
		mvaddch(i, OFFSET_X + 191 + 1, ' ');
		mvaddch(i++, 253, ' ');
	}
	mvprintw(68, 0, "%254c", ' ');
	attroff(COLOR_PAIR(FRAME));
	print_addr();
}

void	print_mem_ncurses(unsigned char *m)
{
	int 	i;

	i = 0;
	print_frame();
	move(OFFSET_Y, OFFSET_X);
	while (i < MEM_SIZE)
	{
		if (g_colors_cor[i])
			attron(COLOR_PAIR(g_colors_cor[i]));
		else
			attron(COLOR_PAIR(EMPTY_MEM));
		pr_byte_ncurses(m[i++], 0);
		addch(' ');
		if ((i % 64) == 0)
			move(OFFSET_Y + i / 64, OFFSET_X);
		attroff(COLOR_PAIR(g_colors_cor[i]));
		attroff(COLOR_PAIR(EMPTY_MEM));
	}
	move(OFFSET_Y, OFFSET_X);;
}

/*NU*/
void	pr_regs(char regs[REG_NUMBER][REG_SIZE])
{
	int		i;
	int		y;

	i = 0;
	while (i < REG_NUMBER)
	{
		y = 0;
		while (y < REG_SIZE)
			ft_putchar(to_num(regs[i][y++]));
		ft_putchar('\n');
		i++;
	}
}
