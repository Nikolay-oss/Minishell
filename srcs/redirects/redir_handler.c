#include "ft_parser.h"
#include <fcntl.h>

/*
	Разобраться какие коды ошибок возвращает баш, если dup или open не срабатывает
	bash: warning: here-document at line 148 delimited by end-of-file (wanted `end')
	148????
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

static void	select_redirect(t_minishell *minishell, t_bool *in2red, char *filename,
	char *redir_type, t_stdstreams *stdstreams)
{
	int	exit_status;

	if (!ft_strcmp(">", redir_type))
	{
		exit_status = ft_redir((const char *)filename,
			O_CREAT | O_WRONLY | O_TRUNC, __S_IWRITE | __S_IREAD, 1);
	}
	else if (!ft_strcmp("<", redir_type))
	{
		exit_status = ft_redir((const char *)filename,
			O_RDONLY, 0, 0);
	}
	else if (!ft_strcmp(">>", redir_type))
	{
		exit_status = ft_redir((const char *)filename,
			O_CREAT | O_WRONLY | O_APPEND, __S_IWRITE | __S_IREAD, 1);
	}
	else if (!ft_strcmp("<<", redir_type))
	{
		exit_status = ft_redir_in2(minishell, (const char *)filename,
			stdstreams);
		if (!exit_status)
		{
			exit_status = ft_redir(".redir_buf",
				O_RDONLY, 0, 0);
			*in2red = 1;
		}
	}
}

static void	exec_cmd(t_minishell *minishell, char **cmd, int redir_pos,
	t_bool in2red)
{
	char	*tmp;

	tmp = *(cmd + redir_pos);
	*(cmd + redir_pos) = NULL;
	select_command(minishell, cmd);
	*(cmd + redir_pos) = tmp;
	if (in2red)
		unlink(".redir_buf");
}

void	redir_handler(t_minishell *minishell, char **cmd)
{
	t_uint			i;
	int				redir_pos;
	t_stdstreams	stdstrms;
	t_bool			in2red;

	i = 0;
	redir_pos = -1;
	in2red = 0;
	save_std_descriptors(&stdstrms);
	while (*(cmd + i))
	{
		if (isredir(**(cmd + i)))
		{
			if (redir_pos == -1)
				redir_pos = i;
			select_redirect(minishell, &in2red, *(cmd + i + 1), *(cmd + i), &stdstrms);
		}
		i++;
	}
	exec_cmd(minishell, cmd, redir_pos, in2red);
	revert_std_descriptors(&stdstrms);
}
