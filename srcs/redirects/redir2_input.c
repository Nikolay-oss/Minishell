#include "ft_parser.h"
#include "readline/readline.h"
#include <fcntl.h>

static int	swap_fd(t_stdstreams *streams1, t_stdstreams *streams2)
{
	if (save_std_descriptors(streams1) < 0)
		return (errno);
	if (revert_std_descriptors(streams2) < 0)
		return (errno);
	return (0);
}

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
	t_stdstreams			fd_cur;
	char					*line;
	static t_uint			strs_count = 0;

	if (swap_fd(&fd_cur, &minishell->stdstreams))
		return (errno);
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			printf("minishell: warning: here-document at line %u delimited by"
				" end-of-file (wanted '%s')\n", strs_count, stop_value);
			break ;
		}
		if (!ft_strcmp(line, stop_value))
			break ;
		if (!f_quotes)
			substitute_vars(minishell, &line);
		ft_putendl_fd(line, fd);
		strs_count++;
	}
	return (swap_fd(&minishell->stdstreams, &fd_cur));
}

int	redir2_input(t_minishell *minishell, const char *stop_value,
	int f_quotes)
{
	int	fd;
	int	ret;

	ret = 0;
	fd = open(minishell->here_document, O_CREAT | O_WRONLY | O_TRUNC,
		__S_IREAD | __S_IWRITE);
	if (fd < 0)
		return (1);
	ret = save_to_heredoc(minishell, stop_value, f_quotes, fd);
	close(fd);
	return (ret);
}
