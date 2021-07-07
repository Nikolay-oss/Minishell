#include "ft_parser.h"
#include <fcntl.h>

static void	select_redirect(t_minishell *minishell, char *redir,
	const char *filename)
{
	if (!ft_strcmp("<", redir))
	{
		minishell->exit_status = ft_redir(filename, O_RDONLY, 0, 0);
	}
	else if (!ft_strcmp(">", redir))
	{
		minishell->exit_status = ft_redir(filename, O_CREAT | O_WRONLY
			| O_TRUNC, 0666, 1);
	}
	else if (!ft_strcmp(">>", redir))
	{
		minishell->exit_status = ft_redir(filename, O_CREAT | O_WRONLY
			| O_APPEND, 0666, 1);
	}
}

static void	redir_dual_input(t_minishell *minishell, t_commands *node_cmd,
	t_bool *dual_redir)
{
	t_uint	i;

	i = 0;
	while (*(node_cmd->cmd + i))
	{
		if (!ft_strcmp("<<", *(node_cmd->cmd + i)))
		{
			*dual_redir = 1;
			minishell->exit_status = redir2_input(minishell,
				*(node_cmd->cmd + i + 1), *(node_cmd->flags_quotes + i + 1));
		}
		i++;
	}
}

static void	exec_cmd(t_minishell *minishell, char **cmd, int redir_pos)
{
	char	**cmd_new;

	if (isredir(**cmd) || minishell->exit_status)
		return ;
	if (redir_pos > 0)
	{
		cmd_new = update_cmd_buf(cmd, redir_pos);
		select_command(minishell, cmd_new);
		destroy_command_buf(cmd_new);
	}
	else
		select_command(minishell, cmd);
	if (file_exists(minishell->here_document))
		unlink(minishell->here_document);
}

static t_bool	redir_handler_utils(t_minishell *minishell, char **cmd,
	t_uint i, int *redir_pos)
{
	if (isredir(**(cmd + i)))
	{
		if (*redir_pos == -1)
			*redir_pos = i;
		select_redirect(minishell, *(cmd + i),
			(const char *)*(cmd + i + 1));
		if (minishell->exit_status)
		{
			print_error(*(cmd + i + 1), errno);
			return (1);
		}
	}
	return (0);
}

void	redir_handler(t_minishell *minishell, t_commands *node_cmd)
{
	t_uint	i;
	int		redir_pos;
	t_bool	dual_redir;

	i = 0;
	redir_pos = -1;
	minishell->exit_status = save_std_descriptors(&minishell->stdstreams);
	dual_redir = 0;
	redir_dual_input(minishell, node_cmd, &dual_redir);
	while (*(node_cmd->cmd + i))
	{
		if (redir_handler_utils(minishell, node_cmd->cmd, i, &redir_pos))
			break ;
		i++;
	}
	if (dual_redir)
		minishell->exit_status = ft_redir(minishell->here_document, O_RDONLY, 0, 0);
	exec_cmd(minishell, node_cmd->cmd, redir_pos);
	revert_std_descriptors(&minishell->stdstreams);
}
