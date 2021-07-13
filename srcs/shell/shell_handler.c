#include "minishell.h"

void	shell_handler(t_minishell *minishell)
{
	heredocs_handler(minishell);
	minishell->cnt_prcs = -1;
	if (minishell->pipes_count > 0)
	{
		ft_pipes(minishell, minishell->commands, 0);
	}
	else
	{
		redir_handler(minishell, minishell->commands, 0, 1);
	}
	if (minishell->heredocs)
		destroy_heredocs(minishell);
}
