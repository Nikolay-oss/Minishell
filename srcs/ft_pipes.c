#include "minishell.h"
#include "wait.h"

void	ft_delay(int count)
{
	while (count > 0)
		count--;
}

void	ft_pipes(t_minishell *minishell, t_commands *node, int fd_old)
{
	int			fd[2]; //0 - read; 1 - write
	int			status;
	pid_t		pid;

	if (!node)
		return;
	if (pipe(fd) == -1)
	{
		minishell->exit_status = errno;
		printf("bash: pipe: %s\n", strerror(errno));
		return ;
	}
	pid = fork();
	ft_delay(2000000);
	if (pid < 0)
	{
		printf("bash: fork: %s\n", strerror(errno));
		minishell->exit_status = errno;
		return ;
	}
	if (pid == 0)
	{
		//// child process
		if (dup2(fd_old, STDIN_FILENO) == -1)
		{
			printf("bash: dup2: %s\n", strerror(errno));
			exit(errno);
		}
		if ((node->next) != NULL)
		{
			if (dup2(fd[1], STDOUT_FILENO) == -1) // подмена дескриптора записи на стдаут
			{
				printf("bash: dup2: %s\n", strerror(errno));
				exit(errno);
			}
		}
		close(fd[0]);
		select_command(minishell, node->cmd, 0);
		exit(0);
		}
		else {
		//// parent process
		close(fd[1]);
		fd_old = fd[0];
//		minishell->exit_status = status;
		}
		node = node->next;
		ft_pipes(minishell, node, fd_old);
		close(fd[0]);
		close(fd[1]);
		waitpid(pid, &status, 0);
		if (node == NULL)
			minishell->exit_status = WIFEXITED(status);
}