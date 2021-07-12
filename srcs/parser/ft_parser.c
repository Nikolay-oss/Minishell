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

t_bool	add_to_f_quotes(t_minishell *minishell, int flag)
{
	int	*flag_copy;

	flag_copy = (int *)malloc(sizeof(int));
	if (!flag_copy)
	{
		ft_malloc_error(minishell);
		return (0);
	}
	*flag_copy = flag;
	ft_push_back(minishell->f_quotes, flag_copy);
	return (1);
}

static t_bool	init_parser_tools(t_minishell *minishell)
{
	minishell->all_commands = ft_create_lst();
	minishell->f_quotes = ft_create_lst();
	minishell->pipes_count = 0;
	if (!minishell->all_commands || !minishell->f_quotes)
	{
		ft_malloc_error(minishell);
		return (0);
	}
	return (1);
}

void	ft_parser(t_minishell *minishell, char *buf)
{
	t_uint	i;

	if (!init_parser_tools(minishell))
		return ;
	i = 0;
	while (*(buf + i))
	{
		i += search_tokens(minishell, buf + i);
		if (minishell->ismem_error)
		{
			i = 0;
			break ;
		}
	}
	if (i > 0)
	{
		if (!analyzer(minishell))
			commands_handler(minishell);
	}
	destroy_command_list(&minishell->commands, &destroy_arr2d);
	ft_lst_clear(&minishell->all_commands, &free);
	ft_lst_clear(&minishell->f_quotes, &free);
}
