#include "minishell.h"

void	shell_handler(t_minishell *minishell)
{
	int	status;

	status = -1;
	if (minishell->pipes_count > 0)
	{
		ft_pipes(minishell, minishell->commands, 0);
	}
	else
	{
		redir_handler(minishell, minishell->commands);
	}
}
