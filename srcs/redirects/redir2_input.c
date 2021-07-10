#include "ft_parser.h"
#include "readline/readline.h"
#include <fcntl.h>

// static int	swap_fd(t_stdstreams *streams1, t_stdstreams *streams2)
// {
// 	if (save_std_descriptors(streams1) == 1)
// 		return (errno);
// 	if (revert_std_descriptors(streams2) == 1)
// 		return (errno);
// 	return (0);
// }

static void	substitute_vars(t_minishell *minishell, char **line)
{
	char	*tmp;

	if (!**line)
		return ;
	tmp = *line;
	*line = get_str_withvars(minishell, *line);
	free(tmp);
}

static int	save_to_heredoc(t_minishell *minishell, const char *stop_value,
	int f_quotes, int fd)
{
	t_stdstreams	fd_cur;
	char			*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (!ft_strcmp(line, stop_value))
			break ;
		if (!f_quotes)
			substitute_vars(minishell, &line);
		ft_putendl_fd(line, fd);
	}
	return (0);
}

int	redir2_input(t_minishell *minishell, const char *stop_value,
	int f_quotes)
{
	int	fd;
	int	ret;

	ret = 0;
	fd = open(minishell->here_document, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (fd < 0)
		return (1);
	ret = save_to_heredoc(minishell, stop_value, f_quotes, fd);
	close(fd);
	return (ret);
}

void	redir_dual_input(t_minishell *minishell, t_commands *node_cmd,
	t_bool *dual_redir)
{
	t_uint	i;
	int		status;

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

char	**update_cmd_buf(char **cmd, int redir_pos)
{
	t_list	*cmd_buf;
	char	**cmd_new;
	t_uint	i;

	cmd_buf = ft_create_lst();
	i = 0;
	while (i < redir_pos)
		ft_push_back(cmd_buf, *(cmd + i++));
	while (*(cmd + i))
	{
		if (isredir(**(cmd + i)))
			i++;
		else
			ft_push_back(cmd_buf, *(cmd + i));
		if (*(cmd + i))
			i++;
	}
	cmd_new = ft_lst_to_strs(cmd_buf);
	ft_lst_clear(cmd_buf, NULL);
	return (cmd_new);
}
