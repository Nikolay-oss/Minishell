/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkenchur <dkenchur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 18:24:09 by dkenchur          #+#    #+#             */
/*   Updated: 2021/06/22 22:07:59 by dkenchur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parser.h"

#define DEBUG

/*
	Примерный алгоритм:
	1. 4 функции поиска:
		1.1 поиск команды
		1.2 поиск аргументов:
			1.2.1 поиск стандартных аргументов (пример: echo hello bird)
			1.2.2 поиск аргументов в кавычках
			1.2.3 интерпретация переменных (символ $)
		1.3 поиск пайпов и редиректов
	2. добавление в список
	3. запись команды и ее аргументов в массив строк (массив строк должен заканчиваться NULL указателем)
*/

t_uint	get_command_size(t_node *node)
{
	t_node	*cur;
	t_uint	size;
	char	c;

	size = 0;
	cur = node;
	while (cur)
	{
		c = *(char *)cur->content;
		if (isredir(c) || ispipe(c))
			break ;
		size++;
		cur = cur->next;
	}
	return (size);
}

char	**create_command_buf(t_minishell *minishell, t_node **node)
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

	node = minishell->commands->head;
	while (node)
	{
		cmd = create_command_buf(minishell, &node);
		if (cmd)
		{
			select_command(minishell, cmd);
			destroy_command_buf(cmd);
		}
		if (node)
			node = node->next;
	}
}

void	ft_parser(t_minishell *minishell, char *buf)
{
	t_uint	i;

	i = 0;
	minishell->commands = ft_create_lst();
	if (!minishell->commands)
	{
		// error
		return ;
	}
	while (*(buf + i))
		i += search_tokens(minishell, buf + i);
	if (i > 0)
		commands_handler(minishell);
	#ifndef DEBUG
		t_node	*cur = minishell->commands->head;
		t_uint	j = 0;

		while (j < minishell->commands->size)
		{
			printf("%s\n", (char *)cur->content);
			j++;
			cur = cur->next;
		}
	#endif
	ft_lst_clear(minishell->commands, &free);
}

// void	ft_parser(t_minishell *minishell, char *buf)
// {
// 	char	**command;

// 	command = ft_split(buf, ' ');
// 	if (*command)
// 	{
// 		select_command(minishell, command);
// 		destroy_command_buf(command);
// 	}
// }
