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
	res->last_live = 0;
	res->n_lives = 0;
	ft_bzero(res->header.prog_name, PROG_NAME_LENGTH + 1);
	ft_bzero(res->header.comment, COMMENT_LENGTH + 1);
	return (res);
}


void	validate_size(unsigned int len, t_player *pl, char *path)
{
	if (len < 3)
		err_small_champ(&pl, path);
	else if (len != pl->header.prog_size)
		invalid_pl_size(&pl, path);
	else if (len > CHAMP_MAX_SIZE)
		err_big_champ(&pl, path);
}
//5 arg
static t_player	*handle_player(char *path, unsigned char *mem, unsigned int cur_mem, int p_num)
{
	int				fd;
	unsigned char	buf[4];
	t_player		*pl;
	unsigned int	len;

	len = 0;
	pl = NULL;
	if ((fd = open(path, O_RDONLY)) < 0)
		return (NULL);
	if (read(fd, buf, 4) >= 0 && (pl = create_player()))
	{
		parse_strtoint(&pl->header.magic, buf, 4);
		read(fd, pl->header.prog_name, PROG_NAME_LENGTH);
		read(fd, buf, 4);
		read(fd, buf, 4);
		parse_strtoint(&pl->header.prog_size, buf, 4);
		read(fd, pl->header.comment, COMMENT_LENGTH);
		read(fd, buf, 4);
		while (read(fd, buf, 1))
		{
			mem[cur_mem + len] = *buf;
			g_colors_cor[cur_mem + len++] = p_num;
		}
		pl->n = (short)p_num;
		validate_size(len, pl, path);
		pl->st_code = cur_mem;
	}
	close(fd);
	return (pl);
}

void			delete_players(t_player **pls)
{
	if (pls && *pls)
	{
		if ((*pls)->next)
			delete_players(&((*pls)->next));
		free(*pls);
		*pls = NULL;
	}
}

void			add_player(t_player **pls, t_player *pl, char *path)
{
	if (pl && pls)
	{
		if (*pls)
			pl->id = (*pls)->id + 1;
		else
			pl->id = 1;
		pl->next = *pls;
		*pls = pl;
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

short int	find_available_player_n(t_player *pls)
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

/*NU*/
//int 			set_player_n(int *flagnum, t_player **pls)
//{
//	if (!pls || !*pls)
//		return (1);
//	if (*flagnum >= 0)
//	{
//		if (player_n_exist(*pls, *flagnum))
//		{
//			delete_players(pls);
//			return (1);
//		}
//		(*pls)->n = (short int)*flagnum;
//	}
//	else
//		(*pls)->n = find_available_player_n(*pls);
//	*flagnum = -1;
//	return (0);
//}

t_player		*handle_players(int ac, char **av, t_flags *fl, unsigned char *mmem)
{
	t_player		*pls;
	int 			i;
	int 			pl_num;
	unsigned int 	cur_mem;
	t_player		*pl;

	cur_mem = 0;
	i = 0;
	pl_num = -1;
	pls = NULL;
	while (++i < ac)
	{
		if (!ft_strcmp("-dump", av[i]) || !ft_strcmp("-n", av[i]))
		{
			i++;
			if (!ft_strcmp("-n", av[i - 1]))
				pl_num = (short int)ft_atoi(av[i]);
			continue;
		}
		else if (!ft_strcmp("-v", av[i]))
			continue;
		else
		{
			/*if (set_player_n(&pl_num, &pl))
				return (NULL);*/
			if (pl_num <= 0)
				pl_num = find_available_player_n(pls);
			else if (player_id_exist(pls, pl_num))
			{
				delete_players(&pls);
				return (NULL);
			}
			pl = handle_player(av[i], mmem, cur_mem, pl_num);
			add_player(&pls, pl, av[i]);
			cur_mem += fl->mem_for_champ;
			pl_num = -1;
		}
	}
	return (pls);
}
