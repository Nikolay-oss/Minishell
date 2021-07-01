#include "ft_parser.h"
// #include "get_next_line.h"
#include "readline/readline.h"
#include <fcntl.h>

static void	read_values(t_minishell *minishell, t_list **strs,
	const char *stop_value, t_stdstreams *stdstreams)
{
	char			*line;
	char			*tmp;
	t_stdstreams	fd_cur;

	save_std_descriptors(&fd_cur);
	revert_std_descriptors(stdstreams);
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
		ft_push_back(*strs, line);
	}
	save_std_descriptors(stdstreams);
	revert_std_descriptors(&fd_cur);
}

int	ft_redir_in2(t_minishell *minishell, const char *stop_value,
	t_stdstreams *stdstreams)
{
	char	*str;
	t_list	*strs;
	t_node	*node_str;
	int		fd;

	strs = ft_create_lst();
	read_values(minishell, &strs, stop_value, stdstreams);
	fd = open(".redir_buf", O_CREAT | O_WRONLY, __S_IREAD | __S_IWRITE);
	if (fd < 0)
	{
		ft_lst_clear(strs, &free);
		return (errno);
	}
	node_str = strs->head;
	while (node_str)
	{
		str = (char *)node_str->content;
		write(fd, str, ft_strlen(str));
		write(fd, "\n", 1);
		node_str = node_str->next;
	}
	close(fd);
	ft_lst_clear(strs, &free);
	return (0);
}
