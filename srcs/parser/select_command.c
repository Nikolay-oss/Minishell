#include "minishell.h"
#include <stdio.h>

void	select_command(t_minishell *minishell, char **command)
{
	if (!ft_strcmp(*command, "echo"))
	{
		ft_echo(command + 1);
	}
	else if (!ft_strcmp(*command, "cd"))
	{
		ft_cd(command[1]);
	}
	else if (!ft_strcmp(*command, "pwd"))
	{

	}
	else if (!ft_strcmp(*command, "export"))
	{

	}
	else if (!ft_strcmp(*command, "unset"))
	{

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
