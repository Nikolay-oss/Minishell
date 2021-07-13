#include "minishell.h"
#include <sys/wait.h>

static	void	ft_delay(int count)
{
	while (count > 0)
		count--;
}

static	void	ft_chd_prcs(const pid_t *pid, int *fd_old, t_commands *node,
							  t_minishell *minishell, int *fd)
{
	if (*pid == 0)
	{
		if (dup2(*fd_old, STDIN_FILENO) == -1)
		{
			printf("bash: dup2: %s\n", strerror(errno));
			exit(errno);
		}
		if ((node->next) != NULL)
		{
			if (dup2(fd[1], STDOUT_FILENO) == -1)
			{
				printf("bash: dup2: %s\n", strerror(errno));
				exit(errno);
			}
		}
		close(fd[0]);
		redir_handler(minishell, node, minishell->cnt_prcs, 0);
		exit((int)minishell->exit_status);
	}
	else
	{
		close(fd[1]);
		*fd_old = fd[0];
	}
}

static void ft_ret_recur(int *fd, const pid_t *pid, t_commands *node,
						 t_minishell *minishell)
{
	int	status;

	close(fd[0]);
	close(fd[1]);
	waitpid(*pid, &status, 0);
	if (node == NULL)
		minishell->exit_status = WIFEXITED(status);
}

void	ft_pipes(t_minishell *minishell, t_commands *node, int fd_old)
{
	int		fd[2];
	pid_t	pid;

	if (!node)
		return;
	if (pipe(fd) == -1)
	{
		minishell->exit_status = errno;
		printf("bash: pipe: %s\n", strerror(errno));
		return ;
	}
	minishell->cnt_prcs++;
	pid = fork();
	ft_delay(2000000);
	if (pid < 0)
	{
		printf("bash: fork: %s\n", strerror(errno));
		minishell->exit_status = errno;
		return ;
	}
	ft_chd_prcs(&pid, &fd_old, node, minishell, fd);
	node = node->next;
	ft_pipes(minishell, node, fd_old);
	ft_ret_recur(fd, &pid, node, minishell);
}