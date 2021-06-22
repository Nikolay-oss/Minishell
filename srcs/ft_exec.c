#include "minishell.h"

void	ft_exec(char *name, char **arv, char **envp)
{
	int	result;

	result = execve(name, arv, envp);
	printf("hey: resul = |%d|", result);
}