#include "minishell.h"
#include <stdio.h>

void	select_command(t_minishell *minishell, char **command)
{
	if (!*command)
		return ;
	if (!ft_strcmp(*command, "echo"))
	{
		ft_echo(command + 1);
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
		minishell->exit_status = ft_export(minishell, command);
	}
	else if (!ft_strcmp(*command, "unset"))
	{
		ft_unset(minishell->env, command); //двумерный массив сам ансет и аргументы
	}
	else if (!ft_strcmp(*command, "env"))
	{
		ft_env(minishell->env);
	}
	else if (!ft_strcmp(*command, "exit"))
	{
		ft_exit(minishell, command);
	}
	else
	{
//		char* argv[] = { "cat", "Makefile",   NULL };
		ft_exec(minishell->env, command);
//		printf("%s: command not found\n", *command);
	}
}
