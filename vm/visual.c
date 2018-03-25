/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amichak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/24 14:31:00 by amichak           #+#    #+#             */
/*   Updated: 2018/03/24 14:31:00 by amichak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	init_visual_color(void)
{
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
	clear();
}

void		service_inf(int proc, t_player *pls, t_flags *fl)
{
	int	i;

	i = 0;
	mvprintw(7, 208, "Current speed: %d     ", fl->speed);
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
				pls->n_lives);
		attroff(COLOR_PAIR(pls->id));
		pls = pls->next;
		i++;
	}
}

void		draw_proc(t_proc *proc)
{
	int	x;
	int	y;

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

void		init_visual(t_flags *fl, unsigned char *m, t_proc *head,
						t_player *pls)
{
	if (fl->v)
	{
		initscr();
		noecho();
		curs_set(0);
		keypad(stdscr, TRUE);
		nodelay(stdscr, TRUE);
		cbreak();
		timeout(-1);
		init_visual_color();
		print_mem_ncurses(m);
		service_inf(count_proc(head), pls, fl);
		draw_proc(head);
	}
	else if (fl->dump == -1)
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

void		end_visual(t_flags *fl, t_player *winner)
{
	if (fl->v)
	{
		if (fl->s)
			system("afplay sounds/maslina.mp3");
		mvprintw(35, 205, "winner = %.30s", winner->header.prog_name);
		mvprintw(36, 205, "Press any key to exit");
		refresh();
		timeout(-1);
		getch();
		endwin();
	}
	else if (fl->dump == -1)
		ft_printf("Contestant %d, \"%s\", has won !\n",
				winner->id, winner->header.prog_name);
}
