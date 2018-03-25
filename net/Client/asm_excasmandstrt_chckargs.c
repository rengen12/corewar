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

void	ft_asmsz(char **files)
{
	int		i;
	char	*asmm;
	char	*name;

	i = -1;
	while (files[++i])
	{
		asmm = ft_sub_strsz("./asm ", 0);
		name = ft_sub_strsz(files[i], '\n');
		ft_reallsz(&asmm, name);
		free(name);
		system(asmm);
		free(asmm);
	}
}

void	ft_execute_asm_and_startsz(char **files)
{
	int		i;
	char	*name;
	int		fd;

	i = -1;
	while (files[++i])
	{
		ft_creat_filesz(files[i]);
		name = ft_sub_strsz(files[i], '\n');
		fd = open(name, O_WRONLY);
		write(fd, files[i] + ft_remove_namesz(files[i]),
		ft_slsz(files[i]) - ft_remove_namesz(files[i]));
		free(name);
	}
	ft_asmsz(files);
	ft_start_warsz(files);
}

char	*ft_sb(char *str)
{
	int		i;
	int		dot;
	char	*res;

	res = ft_sub_strsz(str, 0);
	dot = 0;
	i = 0;
	while (res[i])
	{
		if (res[i] == '.')
			dot = 1;
		i++;
	}
	if (dot == 1)
	{
		while (res[i] != '.')
			i--;
		res[i] = 0;
		return (res);
	}
	else
	{
		free(res);
		return (0);
	}
}

int		ft_check_argssz(int argc, char **argv, char **res_str)
{
	char	*tmp;
	char	*tmp2;
	int		fd;

	if (argc != 3)
		return (0);
	tmp = ft_sub_strsz("./asm ", 0);
	ft_reallsz(&tmp, argv[1]);
	system(tmp);
	free(tmp);
	if (!(tmp2 = ft_sb(argv[1])))
		return (0);
	ft_reallsz(&tmp2, ".cor");
	fd = open(tmp2, O_RDONLY);
	if (fd < 0)
		return (ft_return_0(&tmp2));
	free(tmp2);
	(*res_str) = malloc(sizeof(char));
	(*res_str)[0] = 0;
	ft_realsz(&(*res_str), argv[1] + ft_return_namesz(argv[1]));
	if (ft_check_name((*res_str)) == 0)
		return (0);
	return (1);
}

void	ft_rm_rf_cors(char **names)
{
	int		i;
	char	*rm_rf;

	i = 0;
	while (names[i])
	{
		rm_rf = ft_sub_strsz("rm -rf ", 0);
		ft_reallsz(&rm_rf, names[i]);
		system(rm_rf);
		free(rm_rf);
		i++;
	}
	i = -1;
	while (names[++i])
		free(names[i]);
}
