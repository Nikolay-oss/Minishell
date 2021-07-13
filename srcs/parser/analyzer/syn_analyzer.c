/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syn_analyzer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkenchur <dkenchur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 20:50:03 by dkenchur          #+#    #+#             */
/*   Updated: 2021/07/13 20:50:04 by dkenchur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parser.h"

static t_bool	check_next_token(t_node *node_cmd, t_node *node_f)
{
	if (ispipe(*(char *)node_cmd->content))
	{
		if (ispipe(*(char *)node_cmd->next->content))
		{
			syntax_error("|");
			return (1);
		}
	}
	else if (isredir(*(char *)node_cmd->content))
	{
		if (ispipe(*(char *)node_cmd->next->content))
		{
			syntax_error("|");
			return (1);
		}
		else if (isredir(*(char *)node_cmd->next->content))
		{
			syntax_error((char *)node_cmd->next->content);
			return (1);
		}
	}
	return (0);
}

static t_bool	check_token(t_node *node_cmd, t_node *node_f)
{
	t_bool	iserror;

	iserror = 0;
	if (node_cmd->next && *(int *)node_f->content == 0)
	{
		if (*(int *)node_f->next->content == 0)
			iserror = check_next_token(node_cmd, node_f);
	}
	else
	{
		if (*(int *)node_f->content == 0)
		{
			if (ispipe(*(char *)node_cmd->content))
			{
				syntax_error("|");
				iserror = 1;
			}
			else if (isredir(*(char *)node_cmd->content))
			{
				syntax_error("newline");
				iserror = 1;
			}
		}
	}
	return (iserror);
}

t_bool	analyzer(t_minishell *minishell)
{
	t_node	*node_cmd;
	t_node	*node_f;

	node_cmd = minishell->all_commands->head;
	node_f = minishell->f_quotes->head;
	while (node_cmd)
	{
		if (check_token(node_cmd, node_f))
		{
			minishell->exit_status = 2;
			return (1);
		}
		node_cmd = node_cmd->next;
		node_f = node_f->next;
	}
	return (0);
}
