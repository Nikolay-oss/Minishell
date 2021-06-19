#include "ft_parser.h"
#include "data_types.h"
#include <stdlib.h>
#include <sys/wait.h>

void	destroy_command_buf(char **command)
{
	t_uint	i;

	i = 0;
	while (*(command + i))
		free(*(command + i++));
	free(command);
}

t_uint	isredir(char **command)
{
	t_uint	i;

	i = 0;
	while (*(command + i))
	{
		if (**(command + i) == '>')
			return (i + 1);
		i++;
	}
	return (0);
}

void	ft_parser(t_minishell *minishell, char *buf)
{
	char	**command;
	t_uint	idx;
	pid_t	pid;
	int status;

	command = ft_split(buf, ' ');
	if (*command)
	{
		idx = isredir(command);
		if (idx)
		{
			pid = fork();
			if (pid != -1)
			{
				ft_redir(command, *(command + idx));
			}
			wait(&status);
			printf("%d\n", pid);
			printf("exit code of child process (WEXITSTATUS), status -> %d, %d\n",
				WEXITSTATUS(status), status);
		}
		else
		{
			select_command(minishell, command);
		}
		destroy_command_buf(command);
	}
}
