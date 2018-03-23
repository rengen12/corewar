/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_players.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amichak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 16:10:00 by amichak           #+#    #+#             */
/*   Updated: 2018/03/05 16:10:00 by amichak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static t_player	*create_player(void)
{
	t_player	*res;

	if (!(res = (t_player *)malloc(sizeof(t_player))))
		return (NULL);
	res->next = 0;
	res->n = 0;
	res->header.magic = 0;
	res->header.prog_size = 0;
	res->st_code = 0;
	res->id = 0;
	res->is_last = 0;
	res->last_live = 0;
	res->n_lives = 0;
	ft_bzero(res->header.prog_name, PROG_NAME_LENGTH + 1);
	ft_bzero(res->header.comment, COMMENT_LENGTH + 1);
	return (res);
}


int		validate_size(unsigned int len, t_player *pl, char *path)
{
	if (len < 3)
		return (err_small_champ(&pl, path));
	else if (COREWAR_EXEC_MAGIC != pl->header.magic)
		return (invalid_magic(&pl, path));
	else if (len != pl->header.prog_size)
		return (invalid_pl_size(&pl, path));
	else if (len > CHAMP_MAX_SIZE)
		return (err_big_champ(&pl, path));
	else if (pl->header.prog_name[0] == '\0')
		return (err_nameless_champ(&pl, path));
	return (0);
}

static void 	parse_header_inf(int fd, unsigned char buf[4], t_player *pl)
{
	parse_strtoint(&pl->header.magic, buf, 4);
	read(fd, pl->header.prog_name, PROG_NAME_LENGTH);
	read(fd, buf, 4);
	read(fd, buf, 4);
	parse_strtoint(&pl->header.prog_size, buf, 4);
	read(fd, pl->header.comment, COMMENT_LENGTH);
	read(fd, buf, 4);
}

static t_player	*handle_player(char *path, unsigned char *mem,
								  unsigned int cur_mem, unsigned int p_num)
{
	int				fd;
	unsigned char	buf[4];
	t_player		*pl;
	unsigned int	len;
	static int 		id;

	len = 0;
	pl = NULL;
	if ((fd = open(path, O_RDONLY)) < 0)
		return (NULL);
	if (read(fd, buf, 4) == 4 && (pl = create_player()))
	{
		pl->id = ++id;
		parse_header_inf(fd, buf, pl);
		while (read(fd, buf, 1) > 0)
		{
			mem[cur_mem + len] = *buf;
			g_colors_cor[cur_mem + len++] = id;
		}
		pl->n = (unsigned int)0 - p_num;
		pl->st_code = cur_mem;
		validate_size(len, pl, path);
	}
	close(fd);
	return (pl);
}

void	*delete_players(t_player **pls)
{
	if (pls && *pls)
	{
		if ((*pls)->next)
			delete_players(&((*pls)->next));
		free(*pls);
		*pls = NULL;
	}
	return (NULL);
}

void			add_player(t_player **pls, t_player *pl, char *path)
{
	t_player	*temppl;

	if (pl && pls)
	{
		temppl = *pls;
		pl->next = NULL;
		if (temppl)
		{
			while (temppl->next)
				temppl = temppl->next;
			//pl->id = temppl->id + 1;
			temppl->next = pl;
		}
		else
		{
			//pl->id = 1;
			*pls = pl;
		}
	}
	else
	{
		if (errno)
			perror(path);
		delete_players(pls);
	}
}

int 			player_id_exist(t_player *pls, int id)
{
	while (pls)
	{
		if (pls->id == id)
			return (1);
		pls = pls->next;
	}
	return (0);
}

int 			player_n_exist(t_player *pls, unsigned int n)
{
	while (pls)
	{
		if (pls->n == n)
			return (1);
		pls = pls->next;
	}
	return (0);
}

int		find_available_player_n(t_player *pls)
{
	short int	i;

	i = 1;
	while (1)
	{
		if (player_id_exist(pls, i))
			i++;
		else
			return (i);
	}
}

static void		handle_n(char **av, unsigned int *pl_num, int *i)
{
	if (!ft_strcmp("-n", av[(*i)]))
		*pl_num = (unsigned int)ft_atoi(av[++(*i)]);
}

t_player		*handle_players(int ac, char **av, t_flags *fl, unsigned char *mem)
{
	t_player		*pls;
	int 			i;
	unsigned int	pl_num;
	unsigned int 	cur_mem;

	cur_mem = 0;
	i = 0;
	pl_num = 0;
	pls = NULL;
	while (++i < ac)
		if (!ft_strcmp("-dump", av[i]) || !ft_strcmp("-n", av[i]) ||
				!ft_strcmp("-v", av[i]) || !ft_strcmp("-l", av[i]))
			handle_n(av, &pl_num, &i);
		else
		{
			if (pl_num == 0)
				pl_num = (unsigned int)find_available_player_n(pls);
			else if (player_n_exist(pls, pl_num))
				return (delete_players(&pls));
			add_player(&pls, handle_player(av[i], mem, cur_mem, pl_num), av[i]);
			cur_mem += fl->mem_for_champ;
			pl_num = 0;
		}
	return (pls);
}
