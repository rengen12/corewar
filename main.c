/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amichak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 12:44:00 by amichak           #+#    #+#             */
/*   Updated: 2018/03/05 12:44:02 by amichak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "corewar.h"
#include <ncurses.h>

//direct 4 %
//indirect (otnos) 2
/*NU*/
char	**create_rgs(void)
{
	int		i;
	char	**regs;

	i = 0;
	if (!(regs = (char **)malloc(sizeof(char *) * REG_NUMBER)))
		return (NULL);
	while (i < REG_NUMBER)
		if (!(regs[i++] = ft_strnew(REG_SIZE)))
			return (NULL);
	return (regs);
}

void	start_game(unsigned char *mem, t_proc *prcs)
{
	(void)mem;
	(void)prcs;
}

int		main(int ac, char **av)
{
	unsigned char	*main_memory;
	t_flags		fl;
	t_player	*pls;
	t_proc		*procs;

	if (ac == 1)
		return (pr_usage());
	if (parse_flags(&fl, ac, av))
		return (1);
	if (fl.nplayers > MAX_PLAYERS)
		return (ft_puterrendl("Too many champions"));
	if (!(main_memory = ft_memalloc(MEM_SIZE)))
		return (1);
	if (!(pls = handle_players(ac, av, &fl, main_memory)))
		ft_puterrendl("Error in handling players");
	else
	{
		procs = create_procs(pls);
		print_mem(main_memory);
		/*initscr();                   // Переход в curses-режим
		printw(main);  // Отображение приветствия в буфер
		refresh();                   // Вывод приветствия на настоящий экран
		getch();                     // Ожидание нажатия какой-либо клавиши пользователем
		endwin();                    // Выход из curses-режима. Обязательная команда.*/
		getchar();
		system("clear");
		start_game(main_memory, procs);
	}
	delete_players(&pls);
	free(main_memory);
	return (0);
}
