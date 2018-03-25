/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szverhov <szverhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 18:54:24 by szverhov          #+#    #+#             */
/*   Updated: 2017/10/30 12:15:13 by szverhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

char	**ft_strsplitsz(char *s, char c)
{
	char		**res;
	int			j;
	int			len;
	int			i;

	j = 0;
	len = 0;
	i = -1;
	if (s == 0 || (res = (char**)malloc(sizeof(char*)
		* (count_of_wordssz(s, c) + 1))) == 0)
		return (NULL);
	while (s[++i])
	{
		if (s[i] != c || (s[i + 1] == 0 && s[i] != c))
			len++;
		if ((s[i] == c && len > 0) || (s[i + 1] == 0 && len > 0))
		{
			res[j] = (s[i + 1] == 0 && s[i] != c) ?
			ft_strsubbsz(s, i - len + 1, len) : ft_strsubbsz(s, i - len, len);
			j++;
			len = 0;
		}
	}
	res[j] = 0;
	return (res);
}

void	ft_reallsz(char **str, char *tmp)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new = malloc(sizeof(char) * (ft_slsz(*str) + ft_slsz(tmp)) + 2);
	while ((*str)[i])
	{
		new[i] = (*str)[i];
		i++;
	}
	while (tmp[j])
	{
		new[i] = tmp[j];
		i++;
		j++;
	}
	new[i] = 0;
	free((*str));
	(*str) = new;
}

void	ft_creat_filesz(char *buf)
{
	char	*name;
	int		i;
	char	*tch;

	i = 0;
	tch = ft_sub_strsz("touch ", '\0');
	name = ft_sub_strsz(buf, '\n');
	ft_reallsz(&tch, name);
	free(name);
	system(tch);
	free(tch);
}

int		ft_remove_namesz(char *buf)
{
	int i;

	i = 0;
	while (buf[i] != '\n')
		i++;
	i++;
	return (i);
}

void	ft_start_warsz(char **files)
{
	char	*corewa;
	char	*nam;
	int		i;
	char	**names;

	names = (char**)malloc(sizeof(char*) * 5);
	i = -1;
	corewa = ft_sub_strsz("./corewar -v ", 0);
	while (files[++i])
	{
		nam = ft_sub_strsz(files[i], '.');
		names[i] = ft_sub_strsz(nam, 0);
		ft_reallsz(&names[i], ".cor");
		ft_reallsz(&nam, ".cor ");
		ft_reallsz(&corewa, nam);
		free(nam);
	}
	names[i] = 0;
	system(corewa);
	ft_rm_rf_cors(names);
	free(names);
	free(corewa);
}
