#include "minishell.h"
#include <stdio.h>

void	select_command(t_minishell *minishell, char **command)
{
	minishell->home_path
	= getvar_node(minishell->env, "HOME")->content;
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
		ft_pwd();
	}
	else if (!ft_strcmp(*command, "export"))
	{
		ft_export(minishell, command);
	}
	else if (!ft_strcmp(*command, "unset"))
	{
		ft_unset(minishell->env, command[1]);
	}
	else if (!ft_strcmp(*command, "env"))
	{
		ft_env(minishell->env);
	}
	else if (!ft_strcmp(*command, "exit"))
	{

	}
	else
		printf("%s: command not found\n", *command);
}
