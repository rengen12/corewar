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

void	pr_byte_ncurses(unsigned char n)
{
	addch((chtype)"0123456789abcdef"[n / 16]);
	addch((chtype)"0123456789abcdef"[n % 16]);

}

void	print_mem_ncurses(unsigned char *m)
{
	int 	i;

	i = 0;
	while (i < MEM_SIZE)
	{
		attron(COLOR_PAIR(1));
		pr_byte_ncurses(m[i++]);
		addch(' ');
		if ((i % 64) == 0)
			addch('\n');
	}
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
