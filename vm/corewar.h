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
# include <ncurses.h>

# define LIVE	1
# define LD		2
# define ST		3
# define ADD	4
# define SUB	5
# define AND	6
# define OR		7
# define XOR	8
# define ZJMP	9
# define LDI	10
# define STI	11
# define FORK	12
# define LLD	13
# define LLDI	14
# define LFORK	15
# define AFF	16

# define COLOR_GREY 8
# define EMPTY_MEM 8
# define FRAME 9
# define OFFSET_X 6
# define OFFSET_Y 3

int			g_colors_cor[MEM_SIZE];

# define GET2B(arg) (((arg) & 192) >> 6)
# define IS_REG(arg) (GET2B(arg) == REG_CODE)
# define IS_IND(arg) (GET2B(arg) == IND_CODE)
# define IS_DIR(arg) (GET2B(arg) == DIR_CODE)
# define IS_REGOK(arg) ((arg >= 1) && (arg <= REG_NUMBER))

typedef struct	s_player
{
	int				id;
	unsigned int	n;
	t_header		header;
	unsigned int	st_code;
	unsigned int	n_lives;
	unsigned int	last_live;
	int				is_last;
	struct s_player	*next;
}				t_player;

typedef struct	s_proc
{
	unsigned int	id;
	unsigned int	regs[REG_NUMBER];
	unsigned char	to_ex;
	int				pc;
	int				pc_old;
	short int		carry;
	int				wait;
	int				cyc_to_die;
	t_player		*pl;
	struct s_proc	*next;
}				t_proc;

typedef struct	s_flags
{
	short int		n;
	ssize_t			dump;
	short int		v;
	short int		a;
	int				l;
	unsigned int	cycles;
	short int		nplayers;
	int				mem_for_champ;
	unsigned int	proc_num;
	int				cycle_to_die_def;
	int				cycle_to_die_cur;
	int				cyc_per_sec;
	t_player		*pls;
	int				speed;
	int				vm_on;
	int				s;
}				t_flags;

int				parse_flags(t_flags *fl, int ac, char **av);

unsigned int	get_v_acb(unsigned int opcode, unsigned char *m, t_proc *p,
						int dir_size);
void			set_val_for_mem(unsigned char *m, unsigned int op0, int addr);
int				checkarg(unsigned int opcode, int arg1, int arg2, int arg3);
void			get_val_for_ind(unsigned int *val, unsigned char *m, t_proc *p,
								int idx);
void			handle_live(unsigned char *m, t_proc *p, t_player *pls,
							t_flags *fl);
void			handle_ld(unsigned char *m, t_proc *prc);
void			handle_st(unsigned char *m, t_proc *p, t_flags fl);
void			handle_add(unsigned char *m, t_proc *p);
void			handle_sub(unsigned char *m, t_proc *p);
void			handle_and(unsigned char *m, t_proc *p);
void			handle_or(unsigned char *m, t_proc *p);
void			handle_xor(unsigned char *m, t_proc *p);
void			handle_zjmp(unsigned char *m, t_proc *p);
void			handle_ldi(unsigned char *m, t_proc *p);
void			handle_sti(unsigned char *m, t_proc *p, t_flags fl);
void			handle_fork(unsigned char *m, t_proc *p, t_proc **head,
							t_flags *fl);
void			handle_lld(unsigned char *m, t_proc *p);
void			handle_lldi(unsigned char *m, t_proc *p);
void			handle_lfork(unsigned char *m, t_proc *p, t_proc **head,
								t_flags *fl);
void			handle_aff(unsigned char *m, t_proc *prc, t_flags fl);

void			set_last_pl(t_player *pls);
void			delete_proc(t_proc **head, t_proc **to_del);

void			update_visual(unsigned char *m, unsigned int addr, t_proc *p,
							int size);
void			init_visual(t_flags *fl, unsigned char *m, t_proc *head,
							t_player *pls);
void			end_visual(t_flags *fl, t_player *winner);
void			service_inf(int proc, t_player *pls, t_flags *fl);
int				print_mem(unsigned char *m);
void			print_mem_ncurses(unsigned char *m);
void			proc_caret_rem(int pc);
void			proc_caret_add(int pc);
void			pr_byte_ncurses(unsigned int n, unsigned int new);

void			set_waiting(unsigned char *m, t_proc *p);
void			start_game(unsigned char *mem, t_proc **head, t_flags *fl,
							t_proc *cur);

int				count_proc(t_proc *head);
int				pr_usage(void);
int				player_n_exist(t_player *pls, unsigned int n);
int				find_available_player_n(t_player *pls);
void			reset_players_live(t_player *pls);
void			parse_strtoint(void *var, void *str4, int size);

t_player		*find_winner(t_player *pls);

t_player		*handle_player(char *path, unsigned char *mem,
									unsigned int cur_mem, unsigned int p_num);
t_player		*handle_players(int ac, char **av, t_flags *fl,
								unsigned char *mmem);
void			*delete_players(t_player **pls);

int				prerr_fr(t_player **pl, char *str);
int				invalid_pl_size(t_player **pl, char *str);
int				err_big_champ(t_player **pl, char *str);
int				err_small_champ(t_player **pl, char *str);
int				invalid_magic(t_player **pl, char *str);
int				err_nameless_champ(t_player **pl, char *str);

t_proc			*init_proc_data(int pc, t_player *pl, t_flags *fl);
void			add_proc(t_proc **head, t_proc *new);
t_proc			*create_first_procs(t_player *pls, t_flags *fl);
void			handle_process(unsigned char *m, t_proc *cur, t_proc **head,
								t_flags *fl);
void			vm_off(t_flags *fl);
void			vm_on(t_flags *fl);

#endif
