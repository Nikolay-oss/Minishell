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
}

static void	redir_dual_input(t_minishell *minishell, t_commands *node_cmd)
{
	t_uint	i;

	i = 0;
	while (*(node_cmd->cmd + i))
	{
		if (!ft_strcmp("<<", *(node_cmd->cmd + i)))
			ft_redir_in2(minishell, *(node_cmd->cmd + i + 1), node_cmd->flags_quotes + i);
		i++;
	}
}

static void	exec_cmd(t_minishell *minishell, char **cmd, int redir_pos)
{
	char	*tmp;

	tmp = *(cmd + redir_pos);
	*(cmd + redir_pos) = NULL;
	select_command(minishell, cmd);
	*(cmd + redir_pos) = tmp;
}

void	redir_handler(t_minishell *minishell, t_commands *node_cmd)
{
	t_uint			i;
	int				redir_pos;

	i = 0;
	redir_pos = -1;
	minishell->exit_status = save_std_descriptors(&minishell->stdstreams);
}
