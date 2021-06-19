#include "minishell.h"
#include <fcntl.h>

static char	**copy_args(char **command)
{
	char	**args;
	t_uint	size;
	t_uint	i;

	size = 0;
	while (*(command + size))
	{
		if (**(command + size) == '>')
			break ;
		size++;
	}
	args = (char **)ft_calloc(size + 1, sizeof(char *));
	i = 0;
	while (i < size)
	{
		*(args + i) = ft_strdup(*(command + i));
		i++;
	}
	return (args);
}

static void	destroy_args(char **args)
{
	t_uint	i;

	i = 0;
	while (*(args + i))
		free(*(args + i++));
	free(args);
}

void	ft_redir(char **command, char *str)
{
	int		fd;
	int		new_fd;
	char	**args;

	fd = open(str, O_CREAT | O_WRONLY, S_IRWXU);
	if (fd == -1)
		exit(1);
	new_fd = dup2(fd, 1);
	if (new_fd == -1)
		exit(2);
	args = copy_args(command);
	ft_echo(args + 1);
	destroy_args(args);
	close(fd);
	exit(0);
}
