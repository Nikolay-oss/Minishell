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

static char	**create_command_buf(t_minishell *minishell, t_node **cmd_node,
	t_node **f_node, t_bool **flags)
{
	char	**cmd;
	t_uint	cmd_size;
	t_uint	i;

	cmd_size = get_command_size(*cmd_node);
	cmd = (char **)ft_calloc(cmd_size + 1, sizeof(char *));
	*flags = (t_bool *)malloc(sizeof(t_bool) * cmd_size);
	if (!cmd || !*flags)
		return (NULL); // error
	i = 0;
	while (i < cmd_size)
	{
		*(cmd + i) = ft_strdup((*cmd_node)->content);
		*(*flags + i) = *(t_bool *)(*f_node)->content;
		if (!*(cmd + i))
		{
			destroy_command_buf(cmd);
			return (NULL); // error
		}
		*cmd_node = (*cmd_node)->next;
		*f_node = (*f_node)->next;
		i++;
	}
	return (cmd);
}

void	commands_handler(t_minishell *minishell)
{
	t_node	*cmd_node;
	t_node	*flag_node;
	char	**cmd;
	t_bool	*flags;

	cmd_node = minishell->all_commands->head;
	flag_node = minishell->f_quotes->head;
	while (cmd_node && flag_node)
	{
		cmd = create_command_buf(minishell, &cmd_node, &flag_node, &flags);
		if (cmd)
		{
			add_to_command_list(&minishell->commands, cmd, flags);
			// select_command(minishell, cmd);
			// destroy_command_buf(cmd);
		}
		if (cmd_node && flag_node)
		{
			cmd_node = cmd_node->next;
			flag_node = flag_node->next;
		}
	}
	// ft_exec(minishell->env, minishell->commands->cmd);
	redir_handler(minishell, minishell->commands->cmd);
	/*
		где-то тут должен быть обработчик пайпов
	*/
}
