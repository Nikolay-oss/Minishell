#include "minishell.h"
#include <fcntl.h>

void	shell_handler(t_minishell *minishell)
{
	heredocs_handler(minishell);
	minishell->cnt_prcs = 0;
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

t_bool	launch_dual_redir(t_minishell *minishell, int n_proc)
{
	int status;

	status = 0;
	if (*(minishell->heredocs + n_proc))
	{
		status = ft_redir(*(minishell->heredocs + n_proc), O_RDONLY, 0, 0);
		if (file_exists(*(minishell->heredocs + n_proc)))
		{
			fprintf(stderr, "%s\n", *(minishell->heredocs + n_proc));
			unlink(*(minishell->heredocs + n_proc));
		}
		if (status > 0)
			return (0);
	}
	return (1);
}
