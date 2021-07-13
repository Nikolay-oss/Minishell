/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkenchur <dkenchur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 20:49:41 by dkenchur          #+#    #+#             */
/*   Updated: 2021/07/13 20:49:42 by dkenchur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parser.h"
#include <fcntl.h>

static int	select_redirect(t_minishell *minishell, char *redir,
	const char *filename)
{
	int	status;

	status = -1;
	if (!ft_strcmp("<", redir))
	{
		status = ft_redir(filename, O_RDONLY, 0, 0);
	}
	else if (!ft_strcmp(">", redir))
	{
		status = ft_redir(filename, O_CREAT | O_WRONLY | O_TRUNC,
			FPERMISSIONS, 1);
	}
	else if (!ft_strcmp(">>", redir))
	{
		status = ft_redir(filename, O_CREAT | O_WRONLY | O_APPEND,
			FPERMISSIONS, 1);
	}
	if (status != -1)
		minishell->exit_status = status;
	return (status);
}

static t_bool	exec_cmd(t_minishell *minishell, char **cmd, int redir_pos,
	t_bool newproc)
{
	char	**cmd_new;

	cmd_new = NULL;
	if (redir_pos >= 0)
	{
		if (!update_cmd_buf(cmd, redir_pos, &cmd_new))
			return (0);
		select_command(minishell, cmd_new, newproc);
		destroy_arr2d(cmd_new);
	}
	else
		select_command(minishell, cmd, newproc);
	return (1);
}

static t_bool	redir_handler_utils(t_minishell *minishell, char **cmd,
	t_uint i, int *redir_pos)
{
	int	status;

	status = -1;
	if (isredir(**(cmd + i)))
	{
		if (*redir_pos == -1)
			*redir_pos = i;
		status = select_redirect(minishell, *(cmd + i),
			(const char *)*(cmd + i + 1));
		if (status > 0)
		{
			print_error(*(cmd + i + 1), errno);
			return (0);
		}
	}
	return (1);
}

static t_bool	launch_redirs(t_minishell *minishell, t_commands *node_cmd,
	int *redir_pos)
{
	t_uint	i;

	i = 0;
	while (*(node_cmd->cmd + i))
	{
		if (!redir_handler_utils(minishell, node_cmd->cmd, i, redir_pos))
			return (0);
		i++;
	}
	return (1);
}

t_bool	redir_handler(t_minishell *minishell, t_commands *node_cmd, int n_proc,
	t_bool newproc)
{
	int		r_pos;
	t_bool	status;

	r_pos = -1;
	status = 1;
	if (!save_std_descriptors(&minishell->stdstreams))
	{
		dup_ehandler(minishell);
		return (0);
	}
	if (launch_redirs(minishell, node_cmd, &r_pos))
	{
		if (!launch_dual_redir(minishell, n_proc))
			status = 0;
		if (status == 1 && !exec_cmd(minishell, node_cmd->cmd, r_pos, newproc))
			status = 0;
	}
	else
		status = 0;
	if (!revert_std_descriptors(&minishell->stdstreams))
	{
		status = 0;
		dup_ehandler(minishell);
	}
	return (status);
}
