/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amichak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/24 15:29:00 by amichak           #+#    #+#             */
/*   Updated: 2018/03/24 15:29:00 by amichak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static t_player		*create_player(void)
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

static int			validate(unsigned int len, t_player **pl, char *path)
{
	if (COREWAR_EXEC_MAGIC != (*pl)->header.magic)
		return (invalid_magic(pl, path));
	else if (len > CHAMP_MAX_SIZE)
		return (err_big_champ(pl, path));
	else if (len < 3)
		return (err_small_champ(pl, path));
	else if (len != (*pl)->header.prog_size)
		return (invalid_pl_size(pl, path));
	else if ((*pl)->header.prog_name[0] == '\0')
		return (err_nameless_champ(pl, path));
	return (0);
}

static void			parse_header_inf(int fd, unsigned char buf[4], t_player *pl)
{
	parse_strtoint(&pl->header.magic, buf, 4);
	read(fd, pl->header.prog_name, PROG_NAME_LENGTH);
	read(fd, buf, 4);
	read(fd, buf, 4);
	parse_strtoint(&pl->header.prog_size, buf, 4);
	read(fd, pl->header.comment, COMMENT_LENGTH);
	read(fd, buf, 4);
}

static unsigned int	cp_champ_code(int fd, unsigned char *mem, int id,
									unsigned int cur_m)
{
	unsigned char	buf;
	unsigned int	len;

	len = 0;
	while (read(fd, &buf, 1) > 0)
	{
		mem[cur_m + len] = buf;
		g_colors_cor[cur_m + len++] = id;
		if (len > CHAMP_MAX_SIZE)
			break ;
	}
	return (len);
}

t_player			*handle_player(char *path, unsigned char *mem,
									unsigned int cur_mem, unsigned int p_num)
{
	int				fd;
	unsigned char	buf[4];
	t_player		*pl;
	unsigned int	len;
	static int		id;

	pl = NULL;
	if ((fd = open(path, O_RDONLY)) < 0)
		return (NULL);
	if (read(fd, buf, 4) == 4 && (pl = create_player()))
	{
		pl->id = ++id;
		parse_header_inf(fd, buf, pl);
		len = cp_champ_code(fd, mem, id, cur_mem);
		pl->n = (unsigned int)0 - p_num;
		pl->st_code = cur_mem;
		validate(len, &pl, path);
	}
	close(fd);
	return (pl);
}
