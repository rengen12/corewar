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

#include "server.h"

void	ft_creat_file_sz(char *buf)
{
	char	*name;
	int		i;
	char	*tch;

	i = 0;
	tch = ft_sub_str_sz("touch ", '\0');
	name = ft_sub_str_sz(buf, '\n');
	ft_reall_sz(&tch, name);
	free(name);
	system(tch);
	free(tch);
}

int		ft_remove_name_sz(char *buf)
{
	int i;

	i = 0;
	while (buf[i] != '\n')
		i++;
	i++;
	return (i);
}

void	ft_start_war_sz(char **files)
{
	char	*corewa;
	char	*nam;
	int		i;
	char	**names;

	names = (char**)malloc(sizeof(char*) * 5);
	i = -1;
	corewa = ft_sub_str_sz("./corewar -v ", 0);
	while (files[++i])
	{
		nam = ft_sub_str_sz(files[i], '.');
		names[i] = ft_sub_str_sz(nam, 0);
		ft_reall_sz(&names[i], ".cor");
		ft_reall_sz(&nam, ".cor ");
		ft_reall_sz(&corewa, nam);
		free(nam);
	}
	names[i] = 0;
	system(corewa);
	ft_rm_rf_cors(names);
	free(names);
	free(corewa);
}

void	ft_asm_sz(char **files)
{
	int		i;
	char	*asmm;
	char	*name;

	i = -1;
	while (files[++i])
	{
		asmm = ft_sub_str_sz("./asm ", 0);
		name = ft_sub_str_sz(files[i], '\n');
		ft_reall_sz(&asmm, name);
		free(name);
		system(asmm);
		free(asmm);
	}
}

void	ft_execute_asm_and_start_sz(char **files)
{
	int		i;
	char	*name;
	int		fd;

	i = -1;
	while (files[++i])
	{
		ft_creat_file_sz(files[i]);
		name = ft_sub_str_sz(files[i], '\n');
		fd = open(name, O_WRONLY);
		write(fd, files[i] + ft_remove_name_sz(files[i]),
		ft_sl_sz(files[i]) - ft_remove_name_sz(files[i]));
		free(name);
	}
	ft_asm_sz(files);
	ft_start_war_sz(files);
}
