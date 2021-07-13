/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkenchur <dkenchur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 20:49:06 by dkenchur          #+#    #+#             */
/*   Updated: 2021/07/13 20:49:07 by dkenchur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	create_heredocs_arr(t_minishell *minishell)
{
	char	**heredocs;
	t_uint	size_heredocs;

	size_heredocs = minishell->pipes_count + 1;
	heredocs = (char **)malloc((size_heredocs + 1) * sizeof(char *));
	if (!heredocs)
	{
		ft_malloc_error(minishell);
		return (0);
	}
	*(heredocs + size_heredocs) = NULL;
	minishell->heredocs = heredocs;
	return (1);
}

static void	find_dual_redir(t_commands *node_cmd, int *n_heredoc,
	t_bool *dual_redir)
{
	t_uint	i;

	i = 0;
	while (*(node_cmd->cmd + i))
	{
		if (!ft_strcmp("<<", *(node_cmd->cmd + i))
			&& !*(node_cmd->flags_quotes + i))
		{
			(*n_heredoc)++;
			*dual_redir = 1;
			break ;
		}
		i++;
	}
}

static t_bool	create_filename(t_minishell *minishell, t_commands *node_cmd,
	char **filename, int *n_heredoc)
{
	t_bool	dual_redir;
	char	*n_doc;

	dual_redir = 0;
	find_dual_redir(node_cmd, n_heredoc, &dual_redir);
	if (dual_redir)
	{
		n_doc = ft_itoa(*n_heredoc);
		*filename = ft_strjoin(HEREDOCNAME, n_doc);
		if (!*filename)
		{
			if (n_doc)
				free(n_doc);
			ft_malloc_error(minishell);
			return (0);
		}
		free(n_doc);
	}
	else
	{
		*filename = NULL;
	}
	return (1);
}

void	destroy_heredocs(t_minishell *minishell)
{
	t_uint	i;

	i = 0;
	while (i < minishell->pipes_count + 1)
	{
		if (*(minishell->heredocs + i))
		{
			if (file_exists(*(minishell->heredocs + i)))
				unlink(*(minishell->heredocs + i));
		}
		free(*(minishell->heredocs + i++));
	}
	free(minishell->heredocs);
}

t_bool	heredocs_handler(t_minishell *minishell)
{
	int			n_heredoc;
	t_commands	*node_cmd;
	char		*filename;
	t_uint		i;

	if (!create_heredocs_arr(minishell))
		return (0);
	filename = NULL;
	n_heredoc = 0;
	i = 0;
	node_cmd = minishell->commands;
	while (node_cmd)
	{
		if (!create_filename(minishell, node_cmd, &filename, &n_heredoc))
			return (0);
		*(minishell->heredocs + i) = filename;
		if (!redir_dual_input(minishell, node_cmd, filename))
			return (0);
		node_cmd = node_cmd->next;
		i++;
	}
	return (1);
}
