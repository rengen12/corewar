#include <stdio.h>
#include "libft/libft.h"
#include "corewar.h"

//direct 4 %
//indirect (otnos) 2

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
	proc->carry = '1';
	proc->pc = 0;
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

t_proc	*handle_player(char *path)
{
	int 	fd;
	unsigned char 	*buf;
	int			ret;
	unsigned int magic;

	fd = open(path, O_RDONLY);
	buf = ft_strnew(4);
	read(fd, buf, 4);


	magic = buf[3];
	magic += buf[2] << 8;
	magic += buf[1] << 16;
	magic += buf[0] << 24;
	free(buf);
	close(fd);
}

void	handle_players(int ac, char **av)
{

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
