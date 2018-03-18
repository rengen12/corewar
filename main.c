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



// екстерн
// функц по новому экселю
// унаследование процессом всех регистров и циклов к смерти
// стартовый код бота более тёмным, а новый более светлым
// керри для форка и для джампа
// live для процесса срабатывает. Лайв защитает игроку, если в аргменте будет номер игрока
//		(для победы)
//если вводить ввод номера, то переделать порядковые номера игрока в ид, а н - заданый номер
// цикл смерти уменшается на дельту, если общее количество использованних лайвов больше 20
// макс чекс для того, если 10 раз (проходов сайкл ту дай) не было уменшение на дельту (или в любом случае?)
//пс прыгает на макс возможное значение, которое оно пожет принять (сти октал фф = 7 оффсет)
// сохраяется ли керри после пары команд, которые не изменяю керри
//описать механизм победителя. В случае отсутсвия лайва у чемпа - победитель последний по списку
//		крутить список и с чекать лайв на текущ итер, если нет - последний

//если повредить асб, то каретка двигается, но операция не выполняется
// 		(актуально для функций, которые вносят изменения в память)
//	решень: когда бу разбивать по файлам функц - вынести валидацию арг в отдель функции
//			одна операц  - 1 файл
// !!!тест возможных косяков с приёмом аругента 2 байта и реистра, где потом получается индекс (к шорт инт)

// не все равно ли на негативные числа, ведь если привести к модулю, то так же выходит
// урезание значения регистра при приведении к шорт


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

void	pr_mem_ncurses(unsigned char *m)
{
	clear();
	print_mem_ncurses(m);

	//refresh();
}

void	draw_proc(t_proc *proc)
{
	int	x;
	int y;

	while (proc)
	{
		x = proc->pc % 64 * 3 + OFFSET_X;
		y = proc->pc / 64 + OFFSET_Y;
		mvaddch(y, x, mvinch(y, x) | A_REVERSE);
		mvaddch(y, x + 1, mvinch(y, x + 1) | A_REVERSE);
		proc = proc->next;
	}
	refresh();
	//getch();
}

void	service_inf(int cycle, int proc, t_player *pls)
{
	int 	i;

	i = 0;
	attron(COLOR_PAIR(0));
	mvprintw(10, 205, "cycle = %d", cycle);
	mvprintw(11, 205, "proc = %d", proc);

	while (pls)
	{
		mvprintw(13 + i * 2, 205, "champ %d, name %20s", pls->n, pls->header.prog_name);
		pls = pls->next;
		i++;
	}
	attroff(COLOR_PAIR(0));
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

int 	need_decreace_cycle_to_die(t_player *pls, t_flags *fl)
{
	int 	res;

	res = 0;
	while (pls)
	{
		res += pls->n_lives;
		pls->n_lives = 0;
		pls = pls->next;
	}
	if (fl->cycle_to_die_cur >= NBR_LIVE)
	{
		fl->cycle_to_die_cur = 0;
		return (1);
	}
	return (res >= NBR_LIVE ? 1 : 0);
}

void	start_game(unsigned char *mem, t_proc **head, t_flags *fl, t_player *pls)
{
	t_proc	*cur;
	unsigned int	cycle;

	cycle = 0;
	cur = *head;
	if (fl->v)
	{
		initscr();
		noecho();
		curs_set(0);
		start_color();
		init_color(COLOR_GREY, 350, 350, 350);
		init_color(COLOR_WHITE, 750, 750, 750);
		init_pair(0, COLOR_WHITE, COLOR_BLACK);
		init_pair(1, COLOR_RED, COLOR_BLACK);
		init_pair(2, COLOR_GREEN, COLOR_BLACK);
		init_pair(3, COLOR_BLUE, COLOR_BLACK);
		init_pair(4, COLOR_YELLOW, COLOR_BLACK);
		init_pair(EMPTY_MEM, COLOR_GREY, COLOR_BLACK);
		init_pair(FRAME, COLOR_BLACK, COLOR_WHITE);
		pr_mem_ncurses(mem);
		service_inf(cycle, count_proc(*head), pls);
		draw_proc(*head);
		getch();
	}
	while (cur)
	{
		if (cycle == fl->dump)
		{
			print_mem(mem);
			break ;
		}
		if (cycle && cycle % CYCLE_TO_DIE == 0)
		{
			if (need_decreace_cycle_to_die(pls, fl))
				fl->cycle_to_die_def -= CYCLE_DELTA;
			if (cur->cyc_to_die <= 0)
				delete_proc(head, &cur);
		}
		else
		{
			if (!cur->wait)
				set_waiting(mem, cur);
			cur->wait--;
			if (cur->wait <= 0)
			{
				if (handle_process(mem, cur, head, fl, pls, cycle))
				{
					delete_proc(head, &cur);
					continue ;
				}
			}
		}
		if (cur)
		{
			cur->cyc_to_die--;
			cur = cur->next;
		}
		if (!cur)
		{
			cur = *head;
			cycle++;
			service_inf(cycle, count_proc(*head), pls);
			refresh();

			//halfdelay(100000);
			//getch();
			//timeout(1000);
		}
	}
	if (fl->v)
	{
		mvprintw(25, 205, "winner = %s", "babal");
		refresh();
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
		start_game(main_memory, &procs, &fl, pls);

	}
	delete_players(&pls);
	free(main_memory);
	if (fl.l)
		system("leaks corewar");
	return (0);
}