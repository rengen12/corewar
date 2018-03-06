/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amichak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 19:27:00 by amichak           #+#    #+#             */
/*   Updated: 2018/03/06 19:27:00 by amichak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_proc	*init_proc_data(unsigned int pc, t_player *pl)
{
	t_proc	*proc;
	int		i;
	int		y;

	if (!(proc = (t_proc *)malloc(sizeof(t_proc))))
		return (NULL);
	proc->carry = 1;
	proc->pc = pc;
	proc->pl = pl;
	proc->next = 0;
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

void	add_proc(t_proc **head, t_proc *new)
{
	if (head && new)
	{
		new->next = *head;
		*head = new;
	}
}

t_proc	*create_procs(t_player *pls)
{
	t_proc	*prcs;

	prcs = NULL;
	while (pls)
	{
		add_proc(&prcs, init_proc_data(pls->st_code, pls));
		pls = pls->next;
	}
	return (prcs);
}