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
#include <sys/wait.h>

/*
	Примерный алгоритм:
	1. 4 функции поиска:
		1.1 поиск команды
		1.2 поиск аргументов:
			1.2.1 поиск стандартных аргументов (пример: echo hello bird)
			1.2.2 поиск аргументов в кавычках
			1.2.3 интерпретация переменных (символ $)
		1.3 посик пайпов и редиректов
	2. добавление в список
	3. запись команды и ее аргументов в массив строк (массив строк должен заканчиваться NULL указателем)
*/

t_uint	search_str_in_quotes(char *buf, t_bool *isquote1, t_bool *isquote2)
{
	t_uint	i;

	i = 0;
	while(*(buf + i))
	{
		if (*(buf + i) == '\'')
			change_flag(isquote1);
		else if (*(buf + i) == '"')
			change_flag(isquote2);
		if (*(buf + i) == ' ' && *isquote1 && *isquote2)
			break ;
		i++;
	}
	return (i);
}

t_uint	search_command(char *buf, char **str_cmd)
{
	t_uint	i;
	t_bool	isquote1;
	t_bool	isquote2;
	
	i = 0;
	isquote1 = 0;
	isquote2 = 0;
	while (*(buf + i))
	{
		if (*(buf + i) == '\'')
		{
			isquote2 = 1;
			i += search_str_in_quotes(buf, &isquote1, &isquote2);
		}
		else if (*(buf + i) == '"')
		{
			isquote1 = 1;
			i += search_str_in_quotes(buf, &isquote1, &isquote2);
		}
		if (*(buf + i) == '|' || *(buf + i) == '>')
		{
			copy_command(buf, str_cmd, i);
			return (i);
		}
		i++;
	}
	if (!*str_cmd)
		*str_cmd = ft_strdup(buf);
	return (i);
}

void	ft_parser(t_minishell *minishell, char *buf)
{
	t_uint	i;
	char	*str_cmd;

	i = 0;
	minishell->commands = ft_create_lst();
	if (!minishell->commands)
	{
		// error
		return ;
	}
	while (*(buf + i))
	{
		str_cmd = NULL;
		i += search_command(buf + i, &str_cmd);
		printf("%s\n", str_cmd);
		if (str_cmd)
			ft_push_back(minishell->commands, str_cmd);
		if (*(buf + i))
			i++;
	}
	// temp
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
