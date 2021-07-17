/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkenchur <dkenchur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 20:51:24 by dkenchur          #+#    #+#             */
/*   Updated: 2021/07/15 05:59:02 by dkenchur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>

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

static void	child_proc_handler(char *bin_path, char **cmd, char **envp)
{
	int	status;

	status = 0;
	signals.pid = fork();
	if (signals.pid == 0)
	{
		execve(bin_path, cmd, envp);
	}
	else
	{
		waitpid(signals.pid, &status, 0);
		sigint_save_status(status);
		sigquit_save_status(status);
	}
}

void	ft_exec(t_minishell *minishell, char **cmd, t_bool create_proc)
{
	char	*bin_path;
	char	**envp;

	bin_path = NULL;
	save_path_to_bin(minishell, *cmd, &bin_path);
	if (!bin_path)
		return ;
	envp = ft_lst_to_strs(minishell->env);
	if (!check_envp(minishell, envp, &bin_path))
		return ;
	if (create_proc)
		child_proc_handler(bin_path, cmd, envp);
	else {
		execve(bin_path, cmd, envp);
	}
	destroy_arr2d(envp);
	free(bin_path);
}