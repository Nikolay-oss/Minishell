#include "ft_parser.h"
#include <fcntl.h>

static int	select_redirect(t_minishell *minishell, char *redir,
	const char *filename)
{
	int	status;

	status = -1;
	if (!ft_strcmp("<", redir))
	{
		status = ft_redir(filename, O_RDONLY, 0, 0);
	}
	else if (!ft_strcmp(">", redir))
	{
		status = ft_redir(filename, O_CREAT | O_WRONLY | O_TRUNC,
			FPERMISSIONS, 1);
	}
	else if (!ft_strcmp(">>", redir))
	{
		status = ft_redir(filename, O_CREAT | O_WRONLY | O_APPEND,
			FPERMISSIONS, 1);
	}
	if (status != -1)
		minishell->exit_status = status;
	return (status);
}

static void	exec_cmd(t_minishell *minishell, char **cmd, int redir_pos)
{
	char	**cmd_new;

	if (redir_pos >= 0)
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
	int	status;

	status = -1;
	if (isredir(**(cmd + i)))
	{
		if (*redir_pos == -1)
			*redir_pos = i;
		status = select_redirect(minishell, *(cmd + i),
			(const char *)*(cmd + i + 1));
		if (status > 0)
		{
			print_error(*(cmd + i + 1), errno);
			return (0);
		}
	}
	return (1);
}

static t_bool	launch_redirs(t_minishell *minishell, t_commands *node_cmd,
	int *redir_pos)
{
	t_uint	i;

	i = 0;
	while (*(node_cmd->cmd + i))
	{
		if (!redir_handler_utils(minishell, node_cmd->cmd, i, &redir_pos))
			return (0);
		i++;
	}
	return (1);
}

void	redir_handler(t_minishell *minishell, t_commands *node_cmd)
{
	int		redir_pos;
	t_bool	dual_redir;

	redir_pos = -1;
	if (save_std_descriptors(&minishell->stdstreams))
	{
		dup_ehandler(minishell);
		return ;
	}
	dual_redir = 0;
	// redir_dual_input(minishell, node_cmd, &dual_redir);
	if (launch_redirs(minishell, node_cmd, &redir_pos))
	{
		if (dual_redir)
			minishell->exit_status = ft_redir(minishell->here_document, O_RDONLY, 0, 0);
		exec_cmd(minishell, node_cmd->cmd, redir_pos);
	}
	if (revert_std_descriptors(&minishell->stdstreams))
		dup_ehandler(minishell);
}
