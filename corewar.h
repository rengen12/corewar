/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amichak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/04 15:48:00 by amichak           #+#    #+#             */
/*   Updated: 2018/03/04 15:48:00 by amichak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H
# include "op.h"

typedef struct	s_player
{
	short int		num;
	t_header		header;
	struct s_player	*next;
}				t_player;

typedef struct	s_proc
{
	char		regs[REG_NUMBER][REG_SIZE];
	char		*pc;
	short int	carry;
	t_player	*pl;
}				t_proc;

#endif