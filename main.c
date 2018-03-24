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

static void	init_memory(unsigned char *main_memory)
{
	ft_bzero(g_colors_cor, (size_t)MEM_SIZE * sizeof(int));
	ft_bzero(main_memory, (size_t)MEM_SIZE * sizeof(char));
}

static void	handle_main_data(t_player *pls, unsigned char *m, t_flags *fl)
{
	t_proc			*procs;

	set_last_pl(pls);
	fl->pls = pls;
	procs = create_first_procs(pls, fl);
	start_game(m, &procs, fl, procs);
	delete_players(&pls);
}

int			main(int ac, char **av)
{
	unsigned char	main_memory[MEM_SIZE];
	t_flags			fl;
	t_player		*pls;
	int				ret;

	ret = 0;
	if (ac == 1)
		return (pr_usage());
	init_memory(main_memory);
	if (!parse_flags(&fl, ac, av))
	{
		if (!(pls = handle_players(ac, av, &fl, main_memory)))
			ft_puterrendl("Error in handling players");
		else
			handle_main_data(pls, main_memory, &fl);
	}
	else
		ret = 1;
	if (fl.l)
		system("leaks corewar");
	return (ret);
}
