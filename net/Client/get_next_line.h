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

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFF_SIZE 100

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct	s_clist
{
	char			buf[BUFF_SIZE];
	int				in;
	int				fd;
	int				ret;
	int				count;
	struct s_clist	*next;
	struct s_clist	*prev;
}				t_clist;

int				get_next_line(int fd, char **line);

#endif
