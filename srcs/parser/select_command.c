/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkenchur <dkenchur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 20:50:27 by dkenchur          #+#    #+#             */
/*   Updated: 2021/07/14 23:16:43 by dkenchur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

void	select_command(t_minishell *minishell, char **command, t_bool newproc)
{
	if (!command)// || !*command)
		return ;
	if (!ft_strcmp(*command, "echo"))
	{
		signals.exit_status = ft_echo(command + 1);
	}
	else if (!ft_strcmp(*command, "cd"))
	{
		ft_cd(minishell, command[1]);
	}
	else if (!ft_strcmp(*command, "pwd"))
	{
		signals.exit_status = ft_pwd();
	}
	else if (!ft_strcmp(*command, "export"))
	{
		signals.exit_status = ft_export(minishell, command + 1);
	}
	else if (!ft_strcmp(*command, "unset"))
	{
		ft_unset(minishell->env, command); //двумерный массив сам ансет и аргументы
	}
	else if (!ft_strcmp(*command, "env"))
	{
		signals.exit_status = ft_env(minishell->env);
	}
	else if (!ft_strcmp(*command, "exit"))
	{
		ft_exit(minishell, command);
	}
	else
		ft_exec(minishell, command, newproc);
}
