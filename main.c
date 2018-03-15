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

//direct 4 %
//indirect (otnos) 2





// с регистром 1 тест
// екстерн
// функц по новому экселю
// унаследование процессом всех регистров и циклов к смерти
// стартовый код бота более тёмным, а новый более светлым
// керри для форка и для джампа

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
	while (head && head->next)
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
		proc_caret_rem((*to_del)->pc);
		if ((prev = find_prev_proc(*head, *to_del)))
			prev->next = (*to_del)->next;
		else
			*head = (*to_del)->next;
		temp = (*to_del)->next;
		free(*to_del);
		*to_del = temp;
	}
}

int 	count_proc(t_proc *head)
{
	int 	res;

	res = 0;
	while (head)
	{
		res++;
		head = head->next;
	}
	return (res);
}

void	pr_mem_ncurses(unsigned char *m, unsigned int cycles, t_proc *head)
{
	clear();
	print_mem_ncurses(m);
	printw("\ncycles = %d", cycles);
	printw("\nprocesses = %d", count_proc(head));
	//refresh();
}

void	draw_proc(t_proc *proc)
{
	int	x;
	int y;

	while (proc)
	{
		x = proc->pc % 64 * 3;
		y = proc->pc / 64;
		mvaddch(y, x, mvinch(y, x) | A_REVERSE);
		mvaddch(y, x + 1, mvinch(y, x + 1) | A_REVERSE);
		proc = proc->next;
	}
	refresh();
	//getch();
}

void	service_inf(int cycle, int proc)
{
	mvprintw(68, 0, "cycle = %d", cycle);
	mvprintw(69, 0, "proc = %d", proc);
}

void	set_waiting(unsigned char *m, t_proc *p)
{
	if (LIVE == (m[p->pc]))
		p->wait = 10;
	else if (LD == (m[p->pc]))
		p->wait = 5;
	else if (ST == (m[p->pc]))
		p->wait = 5;
	else if (ADD == (m[p->pc]))
		p->wait = 10;
	else if (SUB == (m[p->pc]))
		p->wait = 10;
	else if (AND == (m[p->pc]))
		p->wait = 6;
	else if (OR == (m[p->pc]))
		p->wait = 6;
	else if (XOR == (m[p->pc]))
		p->wait = 6;
	else if (ZJMP == (m[p->pc]))
		p->wait = 20;
	else if (LDI == (m[p->pc]))
		p->wait = 25;
	else if (STI == (m[p->pc]))
		p->wait = 25;
	else if (FORK == (m[p->pc]))
		p->wait = 800;
	else if (LLD == (m[p->pc]))
		p->wait = 10;
	else if (LLDI == (m[p->pc]))
		p->wait = 50;
	else if (LFORK == (m[p->pc]))
		p->wait = 1000;
	else if (AFF == (m[p->pc]))
		p->wait = 2;
}

void	start_game(unsigned char *mem, t_proc **head, t_flags *fl)
{
	t_proc	*cur;
	unsigned int	cycle;

	cycle = 0;
	cur = *head;
	if (fl->v)
	{
		initscr();
		noecho();
		start_color();
		init_color(COLOR_GREY, 350, 350, 350);
		init_pair(1, COLOR_RED, COLOR_BLACK);
		init_pair(2, COLOR_GREEN, COLOR_BLACK);
		init_pair(3, COLOR_BLUE, COLOR_BLACK);
		init_pair(4, COLOR_YELLOW, COLOR_BLACK);
		init_pair(EMPTY_MEM, COLOR_GREY, COLOR_BLACK);
		pr_mem_ncurses(mem, cycle, *head);
		service_inf(cycle, count_proc(*head));
		draw_proc(*head);
		//getch();

	}
	while (cur)
	{
		if (cycle == fl->dump)
		{
			print_mem(mem);
			break ;
		}
		if (!cur->cyc_to_die)
			delete_proc(head, &cur);
		else
		{
			if (!cur->wait)
				set_waiting(mem, cur);
			cur->wait--;
			if (!cur->wait)
			{
				if (handle_process(mem, cur, head, fl))
				{
					delete_proc(head, &cur);
					continue ;
				}
			}

			cur->cyc_to_die--;
			cur = cur->next;
		}
		if (!cur)
		{
			cur = *head;
			cycle++;
			service_inf(cycle, count_proc(*head));
			refresh();

			//halfdelay(100000);
			getch();
			timeout(1100);
		}
	}
	if (fl->v)
	{
		printw("press to exit");
		getch();
		endwin();
	}
}

/*NU*/
void	init_chtype_field()
{
	int 	i;

	i = 0;
	attron(COLOR_PAIR(EMPTY_MEM));
	while (i < MEM_SIZE)
	{
		g_colors_cor[i] = 0;
		i++;
	}
	attroff(COLOR_PAIR(EMPTY_MEM));
}

int		main(int ac, char **av)
{
	unsigned char	*main_memory;

	t_flags		fl;
	t_player	*pls;
	t_proc		*procs;

	ft_bzero(g_colors_cor, MEM_SIZE * sizeof(int));
	if (ac == 1)
		return (pr_usage());
	if (parse_flags(&fl, ac, av))
		return (1);
	if (fl.nplayers > MAX_PLAYERS)
		return (ft_puterrendl("Too many champions"));
	if (!(main_memory = ft_memalloc(MEM_SIZE)))
		return (1);
	if (!(pls = handle_players(ac, av, &fl, main_memory))) //5 params
		ft_puterrendl("Error in handling players");
	else
	{
		procs = create_procs(pls, &fl);
		//print_mem(main_memory);
		//print_color();
		start_game(main_memory, &procs, &fl);

	}
	delete_players(&pls);
	free(main_memory);
	return (0);
}