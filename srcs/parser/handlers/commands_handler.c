/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkenchur <dkenchur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 19:09:21 by dkenchur          #+#    #+#             */
/*   Updated: 2021/06/29 20:19:38 by dkenchur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parser.h"

void	destroy_command_buf(char **command)
{
	t_uint	i;

	i = 0;
	while (*(command + i))
		free(*(command + i++));
	free(command);
}

static t_uint	get_command_size(t_node *node)
{
	t_node	*cur;
	t_uint	size;
	char	c;

	size = 0;
	cur = node;
	while (cur)
	{
		c = *(char *)cur->content;
		if (ispipe(c))
			break ;
		size++;
		cur = cur->next;
	}
	return (size);
}

static char	**create_command_buf(t_minishell *minishell, t_node **node)
{
	char	**cmd;
	t_uint	cmd_size;
	t_uint	i;

	cmd_size = get_command_size(*node);
	cmd = (char **)ft_calloc(cmd_size + 1, sizeof(char *));
	if (!cmd)
		return (NULL); // error
	i = 0;
	while (i < cmd_size && *node)
	{
		*(cmd + i) = ft_strdup((*node)->content);
		if (!*(cmd + i))
		{
			destroy_command_buf(cmd);
			return (NULL); // error
		}
		*node = (*node)->next;
		i++;
	}
	return (cmd);
}

void	commands_handler(t_minishell *minishell)
{
	t_node	*node;
	char	**cmd;

	node = minishell->all_commands->head;
	while (node)
	{
		cmd = create_command_buf(minishell, &node);
		if (cmd)
		{
			add_to_command_list(&minishell->commands, cmd);
			// select_command(minishell, cmd);
			// destroy_command_buf(cmd);
		}
		if (node)
			node = node->next;
	}
	/*
		где-то тут должен быть обработчик пайпов
	*/
	ft_pipes(minishell);
}
