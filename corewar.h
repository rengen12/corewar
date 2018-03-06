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
# include "libft/libft.h"
# include <stdio.h>
# include <errno.h>

typedef struct	s_player
{
	short int		n;
	t_header		header;
	unsigned int	st_code;
	struct s_player	*next;
}				t_player;

typedef struct	s_proc
{
	unsigned char	regs[REG_NUMBER][REG_SIZE];
	unsigned int	pc;
	short int		carry;
	t_player		*pl;
	struct s_proc	*next;
}				t_proc;

typedef struct	s_flags
{
	short int		n;
	ssize_t			dump;
	short int		v;
	short int		nplayers;
	int 			mem_for_champ;
}				t_flags;

void			print_mem(unsigned char *m);


int				prerr_fr(t_player **pl, char *str);
void			invalid_pl_size(t_player **pl, char *str);
void			err_big_champ(t_player **pl, char *str);
void			err_small_champ(t_player **pl, char *str);

int				pr_usage(void);
int				parse_flags(t_flags *fl, int ac, char **av);

void			parse_int(void *var, void *str4);
char			to_num(char val);

t_player		*handle_players(int ac, char **av, t_flags *fl, unsigned char *mmem);
void			delete_players(t_player **pls);

void			add_proc(t_proc **head, t_proc *new);
t_proc			*init_proc_data(unsigned int pc, t_player *pl);
t_proc			*create_procs(t_player *pls);

#endif