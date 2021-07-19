/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkenchur <dkenchur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 20:50:27 by dkenchur          #+#    #+#             */
/*   Updated: 2021/07/19 23:59:04 by dkenchur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

static void	select_command_tools(t_minishell *minishell, char **command,
	t_bool newproc)
{
	if (!ft_strcmp(*command, "unset"))
	{
		ft_unset(minishell, command);
	}
	else if (!ft_strcmp(*command, "env"))
	{
		g_signals.exit_status = ft_env(minishell->env);
	}
	else if (!ft_strcmp(*command, "exit"))
	{
		ft_exit(minishell, command);
	}
	else
		ft_exec(minishell, command, newproc);
}

void	select_command(t_minishell *minishell, char **command, t_bool newproc)
{
	if (!command)
		return ;
	if (!ft_strcmp(*command, "echo"))
	{
		g_signals.exit_status = ft_echo(command + 1);
	}
	else if (!ft_strcmp(*command, "cd"))
	{
		ft_cd(minishell, command[1]);
	}
	else if (!ft_strcmp(*command, "pwd"))
	{
		g_signals.exit_status = ft_pwd();
	}
	else if (!ft_strcmp(*command, "export"))
	{
		g_signals.exit_status = ft_export(minishell, command + 1);
	}
	else
		select_command_tools(minishell, command, newproc);
}
