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

t_proc	*find_prev_proc(t_proc *head, t_proc *next)
{
	if (head && head->next)
	{
		if (head->next->id == next->id)
			return (head);
		head = head->next;
	}
	return (NULL);
}

void	delete_proc(t_proc **head, t_proc **to_del)
{
	t_proc	*prev;
	t_proc	*temp;

	if (head && to_del && *head && *to_del)
	{
		if ((prev = find_prev_proc(*head, *to_del)))
			prev->next = (*to_del)->next;
		else
			*head = (*to_del)->next;
		temp = (*to_del)->next;
		free(*to_del);
		*to_del = temp;
	}
}

void	start_game(unsigned char *mem, t_proc **head, t_flags *fl)
{
	t_proc	*cur;
	unsigned int	cycle;

	cycle = 0;
	cur = *head;
	while (cur)
	{
		if (!cur->cyc_to_die)
			delete_proc(head, &cur);
		else
		{
			if (!cur->wait)
			{
				if (handle_process(mem, cur, head, fl))
				{
					delete_proc(head, &cur);
					continue ;
				}
			}
			cur->wait--;
			cur->cyc_to_die--;
			cycle++;
			cur = cur->next;
		}
		if (!cur)
			cur = *head;
	}
}

int		main(int ac, char **av)
{
	unsigned char	*main_memory;
	t_flags		fl;
	t_player	*pls;
	t_proc		*procs;

	ft_putnbr(-2 % MEM_SIZE);
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
		procs = create_procs(pls, &fl);
		print_mem(main_memory);
		/*initscr();                   // Переход в curses-режим
		printw("10");  // Отображение приветствия в буфер
		refresh();                   // Вывод приветствия на настоящий экран
		getch();                     // Ожидание нажатия какой-либо клавиши пользователем
		endwin();   */                 // Выход из curses-режима. Обязательная команда.*/
		//getchar();
		//system("clear");
		start_game(main_memory, &procs, &fl);
	}
	delete_players(&pls);
	free(main_memory);
	return (0);
}