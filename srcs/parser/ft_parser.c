/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkenchur <dkenchur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 18:24:09 by dkenchur          #+#    #+#             */
/*   Updated: 2021/06/29 20:12:49 by dkenchur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parser.h"

// #define DEBUG

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

void	ft_parser(t_minishell *minishell, char *buf)
{
	t_uint	i;

	i = 0;
	minishell->all_commands = ft_create_lst();
	if (!minishell->all_commands)
	{
		// error
		return ;
	}
	while (*(buf + i))
		i += search_tokens(minishell, buf + i); // после все в списке
	// if (i > 0)
	// 	commands_handler(minishell);
	#ifndef DEBUG
		t_node	*cur = minishell->all_commands->head;
		t_uint	j = 0;

		while (j < minishell->all_commands->size && cur)
		{
			if ((char *)cur->content)
				printf("%s\n", (char *)cur->content);
			j++;
			cur = cur->next;
		}
	#endif
	destroy_command_list(&minishell->commands, &destroy_command_buf);
	ft_lst_clear(minishell->all_commands, &free);
}
