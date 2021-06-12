#include "minishell.h"
#include "libft.h"
#include <stdio.h>

void	select_command(const char **command)
{
	if (!ft_strcmp(*command, "echo"))
	{

	}
	else if (!ft_strcmp(*command, "cd"))
	{

	}
	else if (!ft_strcmp(*command, "pwd"))
	{
		printf("pwd\n");
	}
	else if (!ft_strcmp(*command, "export"))
	{

	}
	else if (!ft_strcmp(*command, "unset"))
	{

	}
	else if (!ft_strcmp(*command, "env"))
	{

	}
	else if (!ft_strcmp(*command, "exit"))
	{

	}
	else
		printf("%s: command not found\n", *command);
}
