/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkenchur <dkenchur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 20:51:24 by dkenchur          #+#    #+#             */
/*   Updated: 2021/07/15 01:48:26 by dkenchur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>
#include <signal.h>

void	make_path_to_bin(t_minishell *minishell, char *path, char *cmd_bin,
	char **cmd_bin_out)
{
	char	*tmp;

	if (!path)
	{
		signals.exit_status = 127;
		return ;
	}
	tmp = ft_strjoin(path, "/");
	*cmd_bin_out = ft_strjoin(tmp, cmd_bin);
	if (!*cmd_bin_out)
	{
		ft_malloc_error(minishell);
		return ;
	}
	free(tmp);
}

static t_bool	check_envp(t_minishell *minishell, char **envp, char **path)
{
	if (!envp)
	{
		free(*path);
		ft_malloc_error(minishell);
		return (0);
	}
	return (1);
}

void	ft_exec(t_minishell *minishell, char **cmd, t_bool create_proc)
{
	char	*path_to_bin;
	int		status;
	char	**envp;

	path_to_bin = NULL;
	save_path_to_bin(minishell, *cmd, &path_to_bin);
	if (!path_to_bin)
		return ;
	envp = ft_lst_to_strs(minishell->env);
	if (!check_envp(minishell, envp, &path_to_bin))
		return ;
	if (create_proc)
	{
		signal(SIGINT, SIG_IGN);
		signals.pid = fork();
		if (signals.pid == 0)
			execve(path_to_bin, cmd, envp);
		else
		{
			waitpid(signals.pid, &status, 0);
			signals.pid = 0;
		}
		signal(SIGINT, &sigint_handler);
		signals.exit_status = WEXITSTATUS(status);
	}
	else
		execve(path_to_bin, cmd, envp);
	destroy_arr2d(envp);
	free(path_to_bin);
}