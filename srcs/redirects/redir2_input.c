/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir2_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkenchur <dkenchur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 20:49:50 by dkenchur          #+#    #+#             */
/*   Updated: 2021/07/22 14:00:17 by dkenchur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parser.h"
#include "readline/readline.h"
#include <fcntl.h>
#include <term.h>

static t_bool	substitute_vars(t_minishell *minishell, char **line)
{
	char	*tmp;

	tmp = *line;
	*line = get_str_withvars(minishell, *line);
	free(tmp);
	if (minishell->ismem_error)
		return (0);
	return (1);
}

static t_bool	save_to_heredoc(t_minishell *minishell, const char *stop_value,
	int f_quotes, int fd)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (!ft_strcmp(line, stop_value))
		{
			free(line);
			break ;
		}
		if (!f_quotes && *line)
		{
			if (!substitute_vars(minishell, &line))
				return (0);
		}
		ft_putendl_fd(line, fd);
		free(line);
	}
	return (1);
}

t_bool	redir2_input(t_minishell *minishell, const char *stop_value,
	int f_quotes, const char *filename)
{
	int		fd;
	t_bool	ret;

	ret = 1;
	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (fd < 0)
	{
		g_signals.exit_status = errno;
		print_error((char *)filename, errno);
		return (0);
	}
	ret = save_to_heredoc(minishell, stop_value, f_quotes, fd);
	close(fd);
	return (ret);
}

t_bool	redir_dual_input(t_minishell *minishell, t_commands *node_cmd,
	const char *filename)
{
	t_uint	i;
	int		status;

	i = 0;
	status = 1;
	if (!filename)
		return (status);
	while (*(node_cmd->cmd + i))
	{
		if (!ft_strcmp("<<", *(node_cmd->cmd + i))
			&& !*(node_cmd->flags_quotes + i))
		{
			status = redir2_input(minishell, *(node_cmd->cmd + i + 1),
					*(node_cmd->flags_quotes + i + 1), filename);
			if (!status)
				return (0);
		}
		i++;
	}
	return (status);
}

t_bool	update_cmd_buf(char **cmd, int redir_pos, char ***cmd_new)
{
	t_list	*cmd_buf;
	int		i;

	cmd_buf = ft_create_lst();
	if (!cmd_buf)
		return (0);
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
	*cmd_new = ft_lst_to_strs(cmd_buf);
	if (cmd_buf->size != 0 && !*cmd_new)
	{
		ft_lst_clear(&cmd_buf, NULL);
		return (0);
	}
	ft_lst_clear(&cmd_buf, NULL);
	return (1);
}
