#include <time.h>
#include <sys/wait.h>
#include "minishell.h"

void	ft_pipes(t_minishell *minishell, t_commands *node, int fd_old)
{
	int			fd[2]; //0 - read; 1 - write
	int			status;
	pid_t		pid;

	if (!node)
	{
//		close(fd[0]);
//		close(fd[1]);
//		close(fd_old);
//			exit(0);
		return;
	}
	if (pipe(fd) == -1)
	{
		minishell->exit_status = errno;
		printf("bash: pipe: %s\n", strerror(errno));
		return ;
	}
	pid = fork();
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
//		close(fd[1]);
		select_command(minishell, node->cmd, 0);
		exit(0);
		}
		else {
		//// parent process
//			waitpid(pid, &status, 0);
		close(fd[1]);
		fd_old = fd[0];
//			node = node->next;
		minishell->exit_status = status;
		}

		node = node->next;
//		printf("node: |%s|\n", *node->cmd);
//		if (!node)
//		{
//			close(fd[0]);
//			close(fd[1]);
//			close(fd_old);
////			exit(0);
//			return;
//		}
//		if (node && pid != 0)
			ft_pipes(minishell, node, fd_old);
		close(fd[0]);
		close(fd[1]);
//		close(fd_old);
		waitpid(pid, &status, 0);
//	exit(0);
//		else if (node == NULL)
//		{
//			if(pid == 0)
//				return ;
//			else
//			{
//				printf("hello\n");
//				waitpid(pid, &status, 0);
////				return ;
//			}
////			return;
//		}
//		else if (node)
//		{
//			printf("bye\n");
//			waitpid(pid, &status, 0);
//		}
}