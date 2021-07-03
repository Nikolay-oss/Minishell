#include "minishell.h"
#include <sys/wait.h>

int	ft_exec(t_list *env, char **cmd)
{
	int	exit_code;

	if (fork() == 0)
	{
		exit_code = execve("/bin/ls", cmd, NULL);
	}
	else
		wait(&exit_code);
	return (WEXITSTATUS(exit_code));
}