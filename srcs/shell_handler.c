#include "minishell.h"
#include "ft_parser.h"

void	shell_handler(t_minishell *minishell)
{
	int	status;

	status = -1;
	minishell->cnt_prcs = 0;
	if (minishell->pipes_count > 0)
	{
		ft_pipes(minishell, minishell->commands, 0);
	}
	else
	{
		redir_handler(minishell, minishell->commands);
	}
}
