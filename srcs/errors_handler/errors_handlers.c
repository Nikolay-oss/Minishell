#include "ft_parser.h"

t_bool	search_arg_ehandler(t_minishell *minishell, int isquotes, char **arg,
	char *buf)
{
	if (!add_to_f_quotes(minishell, isquotes))
		return (0);
	if (!add_arg(minishell, arg, buf))
		return (0);
	return (1);
}

t_bool	add_pipe_ehandler(t_minishell *minishell, char *buf)
{
	if (!add_command_to_allcommands(minishell, buf, 1))
		return (0);
	if (!add_to_f_quotes(minishell, 0))
		return (0);
	return (1);
}

void	dup_ehandler(t_minishell *minishell)
{
	minishell->exit_status = errno;
	ft_putendl_fd(strerror(errno), 2);
}
