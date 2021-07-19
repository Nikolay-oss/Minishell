/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkenchur <dkenchur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 20:51:24 by dkenchur          #+#    #+#             */
/*   Updated: 2021/07/19 21:43:26 by dkenchur         ###   ########.fr       */
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

static int	check_permission(char *bin_path, int status)
{
	if (status == -1)
	{
		print_error(bin_path, errno);
		status = 126;
	}
	return (status);
}

static void	child_proc_handler(char *bin_path, char **cmd, char **envp)
{
	int	status;

	status = 0;
	signals.pid = fork();
	if (signals.pid == 0)
	{
		status = execve(bin_path, cmd, envp);
		status = check_permission(bin_path, status);
		exit(status);
	}
	else
	{
		waitpid(signals.pid, &status, 0);
		save_status(status);
		// signals.exit_status = WEXITSTATUS(status);
		// sigint_save_status(status);
		// sigquit_save_status(status);
	}
}

void	ft_exec(t_minishell *minishell, char **cmd, t_bool create_proc)
{
	char	*bin_path;
	char	**envp;
	int		status;

	bin_path = NULL;
	status = 0;
	save_path_to_bin(minishell, *cmd, &bin_path);
	if (!bin_path)
		return ;
	envp = ft_lst_to_strs(minishell->env);
	if (!check_envp(minishell, envp, &bin_path))
		return ;
	if (create_proc)
		child_proc_handler(bin_path, cmd, envp);
	else
	{
		status = execve(bin_path, cmd, envp);
		status = check_permission(bin_path, status);
	}
	destroy_arr2d(envp);
	free(bin_path);
}