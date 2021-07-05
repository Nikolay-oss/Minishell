#include "ft_parser.h"
#include <fcntl.h>

/*
	Разобраться какие коды ошибок возвращает баш, если dup или open не срабатывает
	bash: warning: here-document at line 148 delimited by end-of-file (wanted `end')
	148????
	Узнать что делать, если unlink не удалил файл

	sort << "arg" - не искать переменные
	sort << arg - искать переменные
*/

static int	ft_redir(const char *filename, int o_flags, int s_flags,
	t_bool dir_type)
{
	int	fd;
	int	fd2;
	int	ret;

	ret = 0;
	fd = open(filename, o_flags, s_flags);
	if (fd < 0)
		return (1);
	if (dir_type)
		fd2 = STDOUT;
	else
		fd2 = STDIN;
	if (dup2(fd, fd2) < 0)
		ret = errno;
	close(fd);
	return (ret);
}

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

static void	redir_dual_input(t_minishell *minishell, t_commands *node_cmd)
{
	t_uint	i;
	t_bool	tmp_flag;

	i = 0;
	tmp_flag = 0;
	while (*(node_cmd->cmd + i))
	{
		if (!ft_strcmp("<<", *(node_cmd->cmd + i)))
		{
			tmp_flag = 1;
			minishell->exit_status = redir2_input(minishell,
				*(node_cmd->cmd + i + 1), *(node_cmd->flags_quotes + i + 1));
		}
		i++;
	}
	if (tmp_flag)
		minishell->exit_status = ft_redir(minishell->here_document, O_RDONLY, 0, 0);
}

static void	exec_cmd(t_minishell *minishell, char **cmd, int redir_pos)
{
	char	*tmp;

	tmp = *(cmd + redir_pos);
	*(cmd + redir_pos) = NULL;
	select_command(minishell, cmd);
	*(cmd + redir_pos) = tmp;
	if (file_exists(minishell->here_document))
		unlink(minishell->here_document);
}

void	redir_handler(t_minishell *minishell, t_commands *node_cmd)
{
	t_uint	i;
	int		redir_pos;

	i = 0;
	redir_pos = -1;
	minishell->exit_status = save_std_descriptors(&minishell->stdstreams);
	redir_dual_input(minishell, node_cmd);
	while (*(node_cmd->cmd + i))
	{
		if (isredir(**(node_cmd->cmd + i)))
		{
			if (redir_pos == -1)
				redir_pos = i;
			select_redirect(minishell, *(node_cmd->cmd + i),
				(const char *)*(node_cmd->cmd + i + 1));
			if (minishell->exit_status)
			{
				ft_putstr_fd("minishell: ", 2);
				ft_putstr_fd(*(node_cmd->cmd + i + 1), 2);
				write(2, ": ", 2);
				ft_putendl_fd(strerror(errno), 2);
				break ;
			}
		}
		i++;
	}
	if (!minishell->exit_status)
		exec_cmd(minishell, node_cmd->cmd, redir_pos);
	revert_std_descriptors(&minishell->stdstreams);
}
