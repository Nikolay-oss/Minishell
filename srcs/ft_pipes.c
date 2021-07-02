//#include <wait.h>
#include <time.h>
#include <sys/wait.h>
#include "minishell.h"

static void	ft_child_process(t_commands *node, t_minishell *minishell, int *fd, int *fd_old)
{
	if (dup2(*fd_old, STDIN_FILENO) == -1)
	{
		printf("bash: dup2: %s", strerror(errno));
		exit(errno);
	}
	if ((node->next) != NULL)
	{
		if (dup2(fd[1], STDOUT_FILENO) == -1) // подмена дескриптора записи на стдаут
		{
			printf("bash: dup2: %s", strerror(errno));
			exit(errno);
		}
	}
	close(fd[0]);
	select_command(minishell, node->cmd);
	exit(0);
}

static	int	ft_check_error(t_minishell *minishell, pid_t *pid, int *fd)
{
	if (pipe(fd) == -1)
	{
		minishell->exit_status = errno;
		printf("bash: pipe: %s", strerror(errno));
		return (-1);
	}
	*pid = fork();
	if (*pid < 0)
	{
		printf("bash: fork: %s", strerror(errno));
		minishell->exit_status = errno;
		return (-1);
	}
	return (1);
}

void	ft_pipes(t_minishell *minishell)
{
	int			fd[2]; //0 - read; 1 - write
	int			fd_old;
	int			status;
	t_commands	*node;

	fd_old = 0;
	node = minishell->commands;
	while (node)
	{
		if (ft_check_error(minishell, &minishell->pid, fd) == -1)
			break ;
		if (minishell->pid == 0)
			ft_child_process(node, minishell, fd, &fd_old);
		else
		{
			waitpid(minishell->pid, &status, 0);
			close(fd[1]);
			fd_old = fd[0];
			WIFEXITED(status);
			node = node->next;
			minishell->exit_status = status;
		}
	}
	close(fd[0]);
	close(fd[1]);
}