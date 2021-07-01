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

static void	read_values(t_minishell *minishell, t_list **strs,
	const char *stop_value, t_stdstreams *stdstreams)
{
	char			*line;
	t_stdstreams	fd_cur;

	minishell->exit_status = swap_fd(&fd_cur, stdstreams);
	if (minishell->exit_status)
		return ;
	line = NULL;
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			printf("minishell: warning: here-document at line 148 delimited by"
				" end-of-file (wanted '%s')\n", stop_value);
			break ;
		}
		if (!ft_strcmp(line, stop_value))
			break ;
		substitute_vars(minishell, &line);
		ft_push_back(*strs, check_memory(&line));
	}
	minishell->exit_status = swap_fd(stdstreams, &fd_cur);
}

static void	data_output(t_list *strs, int fd)
{
	char	*str;
	t_node	*str_node;

	str_node = strs->head;
	while (str_node)
	{
		str = (char *)str_node->content;
		write(fd, str, ft_strlen(str));
		write(fd, "\n", 1);
		str_node = str_node->next;
	}
}

int	ft_redir_in2(t_minishell *minishell, const char *stop_value,
	t_stdstreams *stdstreams)
{
	t_list	*strs;
	int		fd;

	strs = ft_create_lst();
	read_values(minishell, &strs, stop_value, stdstreams);
	if (minishell->exit_status)
	{
		ft_lst_clear(strs, &free);
		return (errno);
	}
	fd = open(".redir_buf", O_CREAT | O_WRONLY, __S_IREAD | __S_IWRITE);
	if (fd < 0)
	{
		ft_lst_clear(strs, &free);
		return (errno);
	}
	data_output(strs, fd);
	close(fd);
	ft_lst_clear(strs, &free);
	return (0);
}
