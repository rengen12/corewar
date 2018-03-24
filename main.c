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

#include "corewar.h"

//инфу в боковое меню

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
}

void	service_inf(int proc, t_player *pls, t_flags *fl)
{
	int 	i;

	i = 0;
	attron(COLOR_PAIR(0));
	mvprintw(10, 201, "cycle = %d    ", fl->cycles);
	mvprintw(11, 201, "proc = %d    ", proc);
	mvprintw(12, 201, "CYCLES_TO_DIE = %u   ", fl->cycle_to_die_def);
	attroff(COLOR_PAIR(0));
	while (pls)
	{
		attron(COLOR_PAIR(pls->id));
		mvprintw(15 + i * 4, 201, "champ %d, name : %.30s", pls->n,
				 pls->header.prog_name);
		mvprintw(16 + i * 4, 201, "last live :%34d", pls->last_live);
		mvprintw(17 + i * 4, 201, "lives in current period :%20d",
				 fl->cycle_to_die_cur);
		attroff(COLOR_PAIR(pls->id));
		pls = pls->next;
		i++;
	}
}

void	set_waiting(unsigned char *m, t_proc *p)
{
	p->to_ex = m[p->pc];
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
	unsigned int	res;
	static int		max_checks;

	res = 0;
	max_checks++;
	if (max_checks >= MAX_CHECKS)
	{
		max_checks = 0;
		return (1);
	}
	if (fl->cycle_to_die_cur >= NBR_LIVE)
	{
		max_checks = 0;
		fl->cycle_to_die_cur = 0;
		return (1);
	}
	fl->cycle_to_die_cur = 0;
	while (pls)
	{
		res += pls->n_lives;
		pls->n_lives = 0;
		pls = pls->next;
	}
	return (res >= NBR_LIVE ? 1 : 0);
}

void	init_visual_color()
{
	init_color(COLOR_GREY, 350, 350, 350);
	init_color(COLOR_WHITE, 750, 750, 750);
	init_pair(0, COLOR_WHITE, COLOR_BLACK);
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_BLUE, COLOR_BLACK);
	init_pair(4, COLOR_YELLOW, COLOR_BLACK);
	init_pair(EMPTY_MEM, COLOR_GREY, COLOR_BLACK);
	init_pair(FRAME, COLOR_BLACK, COLOR_WHITE);
}

void	init_visual(t_flags *fl, unsigned char *m, t_proc *head, t_player *pls)
{
	if (fl->v)
	{
		initscr();
		noecho();
		curs_set(0);
		start_color();
		init_visual_color();
		clear();
		print_mem_ncurses(m);
		service_inf(count_proc(head), pls, fl);
		draw_proc(head);
	}
	else
	{
		ft_printf("Introducing contestants...\n");
		while (pls)
		{
			ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n",
					  pls->id, pls->header.prog_size, pls->header.prog_name,
					  pls->header.comment);
			pls = pls->next;
		}
	}
}

void	end_visual(t_flags *fl, t_player *winner)
{
	if (fl->v)
	{
		mvprintw(25, 205, "winner = %.30s", winner->header.prog_name);
		mvprintw(26, 205, "Press any key to exit");
		refresh();
		getch();
		endwin();
	}
	else
		ft_printf("Contestant %d, \"%s\", has won !\n",
				  winner->id, winner->header.prog_name);
}

t_player	*find_winner(t_player *pls)
{
	t_player	*winner;

	winner = pls;
	if (pls)
		while (pls)
		{
			if (pls->last_live >= winner->last_live || (winner->last_live == 0
													  && pls->is_last))
				winner = pls;
			pls = pls->next;
		}
	return (winner);
}

void	reset_players_live(t_player *pls)
{
	if (pls)
		while (pls)
		{
			pls->n_lives = 0;
			pls = pls->next;
		}
}

void	start_game(unsigned char *mem, t_proc **head, t_flags *fl, t_player *pls)
{
	t_proc			*cur;
	unsigned int	local_cycle;


	local_cycle = 0;
	cur = *head;
	init_visual(fl, mem, *head, pls);
	while (cur)
	{
		if (fl->cycles == fl->dump)
		{
			print_mem(mem);
			break ;
		}
		if (local_cycle && (local_cycle % fl->cycle_to_die_def) == 0)
		{
			if (!cur->next && need_decreace_cycle_to_die(pls, fl))
				fl->cycle_to_die_def -= CYCLE_DELTA;

			if (!cur->next)
				local_cycle = 0;
			if (fl->cycle_to_die_def < 0)
			{
				cur = *head;
				while (cur)
					delete_proc(head, &cur);
			}
			if (cur && cur->cyc_to_die <= 0)
			{
				delete_proc(head, &cur);
				if (!cur)
					cur = *head;
				continue ;
			}
		}
		else
		{
			if (cur->wait <= 0)
				set_waiting(mem, cur);
			cur->wait--;
			if (cur->wait <= 0)
				handle_process(mem, cur, head, fl, pls);
		}
		if (cur)
		{
			cur->cyc_to_die--;
			cur = cur->next;
		}
		if (!cur)
		{
			cur = *head;
			fl->cycles++;
			local_cycle++;
			service_inf(count_proc(*head), pls, fl);
			reset_players_live(pls);
			refresh();
		}
	}
	end_visual(fl, find_winner(pls));
}



static void	init_memory(unsigned char *main_memory)
{
	ft_bzero(g_colors_cor, MEM_SIZE * sizeof(int));
	ft_bzero(main_memory, MEM_SIZE * sizeof(char));

}

static void	prepare_main_data(t_player *pls, unsigned char *m, t_flags *fl)
{
	t_proc			*procs;

	fl->pls = pls;
	set_last_pl(pls);
	procs = create_procs(pls, fl);
	start_game(m, &procs, fl, pls);
	delete_players(&pls);
}

int			main(int ac, char **av)
{
	unsigned char	main_memory[MEM_SIZE];
	t_flags			fl;
	t_player		*pls;

	int 			ret;

	ret = 0;
	if (ac == 1)
		return (pr_usage());
	init_memory(main_memory);
	if (!parse_flags(&fl, ac, av))
	{
		if (!(pls = handle_players(ac, av, &fl, main_memory)))
			ft_puterrendl("Error in handling players");
		else
			prepare_main_data(pls, main_memory, &fl);
	}
	else
		ret = 1;
	if (fl.l)
		system("leaks corewar");
	return (ret);
}
