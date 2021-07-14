/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkenchur <dkenchur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 21:23:06 by brice             #+#    #+#             */
/*   Updated: 2021/07/15 02:18:55 by dkenchur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>

static	void	ft_delay(int count)
{
	while (count > 0)
		count--;
}

static	void	ft_chd_prcs(const pid_t *pid, t_commands *node,
							  t_minishell *minishell, int *fd)
{
	if (*pid == 0)
	{
		if (dup2(minishell->fd_old, STDIN_FILENO) == -1)
		{
			print_error("dup2", errno);
			exit(errno);
		}
		if ((node->next) != NULL)
		{
			if (dup2(fd[1], STDOUT_FILENO) == -1)
			{
				print_error("dup2", errno);
				exit(errno);
			}
		}
		close(fd[0]);
		redir_handler(minishell, node, minishell->cnt_prcs, 0);
		exit(signals.exit_status);
	}
	else
	{
		close(fd[1]);
		minishell->fd_old = fd[0];
	}
}

static void	ft_ret_recur(int *fd, pid_t *pid, t_commands *node)
{
	int	status;

	close(fd[0]);
	close(fd[1]);
	signals.pid = *pid;
	waitpid(*pid, &status, 0);
	if (node == NULL)
	{
		if (!signals.sig_int)
		{
			signals.exit_status = WEXITSTATUS(status);
			signals.sig_int = 0;
		}
	}
}

void	ft_pipes(t_minishell *minishell, t_commands *node, int fd_old)
{
	int		fd[2];
	pid_t	pid;

	if (!node)
		return ;
	if (pipe(fd) == -1)
	{
		minishell->exit_status = errno;
		print_error("pipe", errno);
		return ;
	}
	minishell->cnt_prcs++;
	pid = fork();
	ft_delay(2000000);
	if (pid < 0)
	{
		print_error("fork", errno);
		minishell->exit_status = errno;
		return ;
	}
	minishell->fd_old = fd_old;
	ft_chd_prcs(&pid, node, minishell, fd);
	node = node->next;
	ft_pipes(minishell, node, minishell->fd_old);
	ft_ret_recur(fd, &pid, node);
}
