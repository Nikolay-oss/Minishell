#include "minishell.h"
#include <stdio.h>

void	select_command(t_minishell *minishell, char **command, t_bool newproc)
{
	if (!command)// || !*command)
		return ;
	if (!ft_strcmp(*command, "echo"))
	{
		minishell->exit_status = ft_echo(command + 1);
	}
	else if (!ft_strcmp(*command, "cd"))
	{
		ft_cd(minishell, command[1]);
	}
	else if (!ft_strcmp(*command, "pwd"))
	{
		minishell->exit_status = ft_pwd();
	}
	else if (!ft_strcmp(*command, "export"))
	{
		minishell->exit_status = ft_export(minishell, command + 1);
	}
	else if (!ft_strcmp(*command, "unset"))
	{
		ft_unset(minishell->env, command); //двумерный массив сам ансет и аргументы
	}
	else if (!ft_strcmp(*command, "env"))
	{
		minishell->exit_status = ft_env(minishell->env);
	}
	else if (!ft_strcmp(*command, "exit"))
	{
		ft_exit(minishell, command);
	}
	else
		ft_exec(minishell, command, newproc);
}
