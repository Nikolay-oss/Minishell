#include "ft_parser.h"
#include <fcntl.h>
#include <sys/stat.h>

/*
	Разобраться какие коды ошибок возвращает баш, если dup или open не срабатывает
	bash: warning: here-document at line 148 delimited by end-of-file (wanted `end')
	148????
	Узнать что делать, если unlink не удалил файл

	sort << "arg" - не искать переменные
	sort << arg - искать переменные
*/

t_bool	file_exists(const char *filename)
{
	struct stat	buf;
	int			ret;

	ret = stat(filename, &buf);
	if (ret < 0)
		return (0);
	else
		return (1);
}

static int	ft_redir(const char *filename, int o_flags, int s_flags,
	t_bool dir_type)
{
	int	fd;
	int	fd2;
	int	ret;

	ret = 0;
	fd = open(filename, o_flags, s_flags);
	if (fd < 0)
		return (errno);
	if (dir_type)
		fd2 = STDOUT;
	else
		fd2 = STDIN;
	if (dup2(fd, fd2) < 0)
		ret = errno;
	close(fd);
	return (ret);
}

static void	select_redirect(t_minishell *minishell, char **cmd,
	t_bool f_quotes)
{
	if (!ft_strcmp(">", *cmd))
	{
		minishell->exit_status = ft_redir((const char *)(*(cmd + 1)),
			O_CREAT | O_WRONLY | O_TRUNC, __S_IWRITE | __S_IREAD, 1);
	}
	else if (!ft_strcmp("<", *cmd))
	{
		minishell->exit_status = ft_redir((const char *)(*(cmd + 1)),
			O_RDONLY, 0, 0);
	}
	else if (!ft_strcmp(">>", *cmd))
	{
		minishell->exit_status = ft_redir((const char *)(*(cmd + 1)),
			O_CREAT | O_WRONLY | O_APPEND, __S_IWRITE | __S_IREAD, 1);
	}
	else if (!ft_strcmp("<<", *cmd))
	{
		minishell->exit_status = ft_redir_in2(minishell,
			(const char *)(*(cmd + 1)), f_quotes);
		if (!minishell->exit_status)
			minishell->exit_status = ft_redir(".redir_buf", O_RDONLY, 0, 0);
	}
}

static void	exec_cmd(t_minishell *minishell, char **cmd, int redir_pos)
{
	char	*tmp;

	tmp = *(cmd + redir_pos);
	*(cmd + redir_pos) = NULL;
	select_command(minishell, cmd);
	*(cmd + redir_pos) = tmp;
	if (file_exists(".redir_buf"))
		minishell->exit_status = unlink(".redir_buf");
}

void	redir_handler(t_minishell *minishell, t_commands *node_cmd)
{
	t_uint			i;
	int				redir_pos;

	i = 0;
	redir_pos = -1;
	minishell->exit_status = save_std_descriptors(&minishell->stdstreams);
	while (*(node_cmd->cmd + i))
	{
		if (isredir(**(node_cmd->cmd + i)))
		{
			if (redir_pos == -1)
				redir_pos = i;
			select_redirect(minishell, node_cmd->cmd + i,
				*(node_cmd->flags_quotes + i + 1));
			if (minishell->exit_status)
				break ;
		}
		i++;
	}
	if (!minishell->exit_status)
		exec_cmd(minishell, node_cmd->cmd, redir_pos);
	minishell->exit_status = revert_std_descriptors(&minishell->stdstreams);
}
