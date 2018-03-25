/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_events.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amichak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/24 21:06:00 by amichak           #+#    #+#             */
/*   Updated: 2018/03/24 21:06:00 by amichak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	vm_off(t_flags *fl)
{
	fl->vm_on = 0;
	mvprintw(5, 211, "**PAUSED**");
	timeout(-1);
}

void	vm_on(t_flags *fl)
{
	fl->vm_on = 1;
	mvprintw(5, 211, "***WORK***");
	timeout(1000 / fl->speed - 1);
}
