#include <stdio.h>
#include "libft/libft.h"
#include "corewar.h"

//direct 4 %
//indirect (otnos) 2
/*NU*/
char	**create_rgs(void)
{
	int		i;
	char	**regs;

	i = 0;
	if (!(regs = (char **)malloc(sizeof(char *) * REG_NUMBER)))
		return (NULL);
	while (i < REG_NUMBER)
		if (!(regs[i++] = ft_strnew(REG_SIZE)))
			return (NULL);
	return (regs);
}

char	to_num(char val)
{
	if (val >= 0 && val <= 9)
		return (val + 48);
	return (0);
}

/*NU*/
void	pr_regs(char regs[REG_NUMBER][REG_SIZE])
{
	int		i;
	int		y;

	i = 0;
	while (i < REG_NUMBER)
	{
		y = 0;
		while (y < REG_SIZE)
			ft_putchar(to_num(regs[i][y++]));
		ft_putchar('\n');
		i++;
	}
}

t_proc	*init_proc_data(void)
{
	t_proc	*proc;
	int		i;
	int		y;

	if (!(proc = (t_proc *)malloc(sizeof(t_proc))))
		return (NULL);
	proc->carry = 1;
	proc->pc = 0;
	proc->pl = 0;
	i = 0;
	while (i < REG_NUMBER)
	{
		y = 0;
		while (y < REG_SIZE)
			proc->regs[i][y++] = 0;
		i++;
	}
	return (proc);
}

t_player	*create_player(void)
{
	t_player	*res;

	if (!(res = (t_player *)malloc(sizeof(t_player))))
		return (NULL);
	res->next = 0;
	res->n = 0;
	res->header.magic = 0;
	res->header.prog_size = 0;
	ft_bzero(res->header.prog_name, PROG_NAME_LENGTH + 1);
	ft_bzero(res->header.comment, COMMENT_LENGTH + 1);
	return (res);
}

t_player	*handle_player(char *path)
{
	int				fd;
	unsigned char	buf[4];
	t_player		*pl;
	int 			len;

	len = 0;
	if ((fd = open(path, O_RDONLY)) < 0)
		return (NULL);
	if (read(fd, buf, 4) >= 0 && (pl = create_player()))
	{
		pl->header.magic = buf[3];
		pl->header.magic += buf[2] << 8;
		pl->header.magic += buf[1] << 16;
		pl->header.magic += buf[0] << 24;
		read(fd, pl->header.prog_name, PROG_NAME_LENGTH);
		read(fd, buf, 4);
		read(fd, buf, 4);
		pl->header.prog_size = buf[3];
		pl->header.prog_size += buf[2] << 8;
		pl->header.prog_size += buf[1] << 16;
		pl->header.prog_size += buf[0] << 24;
		read(fd, pl->header.comment, COMMENT_LENGTH);
		read(fd, buf, 4);
		while (read(fd, buf, 1))
			len++;
		if (len != pl->header.prog_size)
		{
			free(pl);
			pl = NULL;
		}
	}
	close(fd);
	return (pl);
}

void	handle_players(int ac, char **av)
{
	handle_player(av[1]);
}

int		main(int ac, char **av)
{
	char	*main_memory;
	char	**regs;
	t_proc	*proc;

	if (!(main_memory = ft_memalloc(MEM_SIZE)))
		return (1);
	//proc = init_proc_data();
	//pr_regs(proc->regs);
	handle_players(ac, av);
	return (0);
}
