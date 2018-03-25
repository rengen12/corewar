/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szverhov <szverhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/26 14:31:43 by szverhov          #+#    #+#             */
/*   Updated: 2017/11/03 12:27:15 by szverhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int		ft_list(t_clist **list, int fd, t_clist *nex, t_clist *pre)
{
	t_clist *tmp;

	if (fd == -999)
	{
		tmp = (*list);
		if ((*list)->prev)
			(*list)->prev->next = (*list)->next;
		if (tmp->next)
			tmp->next->prev = tmp->prev;
		free(tmp);
		*list = 0;
		return (0);
	}
	if (!((*list) = (t_clist*)malloc(sizeof(t_clist))))
		return (0);
	(*list)->count = 0;
	(*list)->in = 0;
	(*list)->fd = fd;
	(*list)->ret = 0;
	(*list)->next = nex;
	(*list)->prev = pre;
	(*list)->buf[0] = 0;
	if ((*list)->ret == -1)
		return (ft_list(&(*list), -999, 0, 0));
	return (1);
}

static int		check_fd(t_clist **list, int fd, int flag, char **line)
{
	int res;

	if (flag == -999 || flag == -888)
	{
		free(*line);
		*line = 0;
		ft_list(&(*list), -999, 0, 0);
		return (flag == -999 ? -1 : 0);
	}
	res = 1;
	while ((*list)->prev)
		(*list) = (*list)->prev;
	while ((*list)->next)
	{
		if (fd == (*list)->fd)
			return (1);
		(*list) = (*list)->next;
	}
	if (fd == (*list)->fd)
		return (1);
	res = ft_list(&((*list)->next), fd, 0, (*list));
	(*list) = (*list)->next;
	return (res);
}

static int		ft_read_more(t_clist **list, char **str, int *i)
{
	char	*tmp;
	int		s_l;
	int		j;
	int		k;

	j = 0;
	k = 0;
	s_l = (*i) + 1;
	if (!((*list)->ret = read((*list)->fd, (*list)->buf, BUFF_SIZE)))
		return (1);
	(*list)->in = 0;
	(*list)->count = (*list)->ret;
	if ((*list)->ret == -1)
		return (ft_list(&(*list), -999, 0, 0));
	tmp = (char*)malloc(sizeof(char) * (s_l + ((*list)->ret)));
	while (s_l-- && (*list)->ret != 0)
		tmp[k++] = (*str)[j++];
	tmp[k] = 0;
	free((*str));
	(*str) = tmp;
	while ((*list)->count != 0 && (*list)->buf[((*list)->in)] != '\n' &&
	(*list)->ret && (*list)->count--)
		(*str)[(*i)++] = (*list)->buf[((*list)->in)++];
	(*str)[*i] = 0;
	return (1);
}

int				ft_init_line_list(const int fd, char **line, t_clist **list)
{
	if (!line || fd < 0 || BUFF_SIZE < 1)
		return (-1);
	if (!((*line) = (char*)malloc(sizeof(char) * (BUFF_SIZE + 2))))
		return (-1);
	if ((*list) == 0)
		if (!(ft_list(&(*list), fd, 0, 0)))
			return (check_fd(&(*list), fd, -999, &(*line)));
	if (check_fd(&(*list), fd, 0, &(*line)) == 0)
		return (check_fd(&(*list), fd, -999, &(*line)));
	return (1);
}

int				get_next_line(const int fd, char **line)
{
	static t_clist	*list;
	int				i;

	if (fd == -1234 && list)
		return (ft_list(&(list), -999, 0, 0));
	if (ft_init_line_list(fd, &(*line), &list) == -1)
		return (-1);
	i = 0;
	if (list->ret == 0)
	{
		list->ret = read(fd, list->buf, BUFF_SIZE);
		list->count = list->ret > 0 ? list->ret : 0;
	}
	while (list->count != 0 && list->buf[(list->in)] != '\n' &&
	list->ret != 0 && list->count--)
		(*line)[i++] = list->buf[(list->in)++];
	(*line)[i] = 0;
	while (list->count == 0 && list->ret > 0)
		if ((ft_read_more(&list, &(*line), &i)) <= 0)
			return (check_fd(&list, fd, -999, &(*line)));
	if (list->buf[list->in] == '\n' && list->count--)
		list->in++;
	if (list->ret == 0 && i == 0)
		return (check_fd(&list, fd, -888, &(*line)));
	return (1);
}
