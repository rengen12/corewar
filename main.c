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

t_proc	*init_proc_data(void)
{
	t_proc	*proc;
	int		i;
	int		y;

	if (!(proc = (t_proc *)malloc(sizeof(t_proc))))
		return (NULL);
	proc->carry = 1;
	proc->pc = 0;
	proc->pl = 0;
	i = 0;
	while (i < REG_NUMBER)
	{
		y = 0;
		while (y < REG_SIZE)
			proc->regs[i][y++] = 0;
		i++;
	}
	return (proc);
}

int 	fill_memory()
{
	//char	**regs;
	//t_proc	*proc;
	//proc = init_proc_data();
	//pr_regs(proc->regs);
	return (0);
}

int		main(int ac, char **av)
{
	char	*main_memory;
	t_flags		fl;
	t_player	*pls;


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

	}
	delete_players(&pls);
	free(main_memory);
	return (0);
}
