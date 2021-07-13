/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkenchur <dkenchur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 20:50:07 by dkenchur          #+#    #+#             */
/*   Updated: 2021/07/13 20:50:08 by dkenchur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parser.h"

#define MAXLEN 4096

static void	add_to_arg(t_minishell *minishell, char **arg, char *new_arg)
{
	char	*tmp;

	if (*arg)
	{
		tmp = *arg;
		*arg = ft_strjoin(*arg, new_arg);
		free(tmp);
	}
	else
		*arg = ft_strdup(new_arg);
	if (!*arg)
		ft_malloc_error(minishell);
}

static void	simple_arg_handler(t_minishell *minishell, char **arg, char *buf)
{
	char	*new_arg;

	if (minishell->all_commands->tail
		&& *(int *)minishell->f_quotes->tail->content == 0
		&& !ft_strcmp("<<", (char *)minishell->all_commands->tail->content))
	{
		new_arg = NULL;
	}
	else
	{
		new_arg = get_str_withvars(minishell, buf);
	}
	if (minishell->ismem_error)
		return ;
	if (new_arg)
	{
		add_to_arg(minishell, arg, new_arg);
		free(new_arg);
	}
	else
		add_to_arg(minishell, arg, buf);
}

static t_uint	quote_handler(t_minishell *minishell, char **arg, char *buf, char type)
{
	t_uint	i;
	char	chr_old;

	if (minishell->ismem_error)
		return (MAXLEN);
	i = get_endquote_idx(buf, type);
	if (i > 0)
	{
		chr_old = *(buf + i);
		*(buf + i) = 0;
		if (type == '\"')
			simple_arg_handler(minishell, arg, buf);
		else
			add_to_arg(minishell, arg, buf);
		*(buf + i) = chr_old;
	}
	if (*(buf + i) == type)
		i++;
	if (minishell->ismem_error)
		return (MAXLEN);
	return (i);
}

static void	arg_handler_tool(char *buf, t_uint *i_end, char *quote_type)
{
	while (!ft_memchr("\"'", *(buf + *i_end), 3))
			(*i_end)++;
	*quote_type = *(buf + *i_end);
}

void	arg_handler(t_minishell *minishell, char **arg, char *buf, t_uint len)
{
	t_uint	i_start;
	t_uint	i_end;
	char	quote_type;
	char	*p_quote;

	init_range(&i_start, &i_end, 0, 0);
	while (i_start < len)
	{
		arg_handler_tool(buf, &i_end, &quote_type);
		if (i_end > i_start)
		{
			p_quote = buf + i_end;
			*(buf + i_end) = 0;
			simple_arg_handler(minishell, arg, buf + i_start);
			i_end += quote_handler(minishell, arg, buf + i_end, quote_type);
			*p_quote = quote_type;
		}
		else
		{
			if (i_end < len)
				i_end++;
			i_end += quote_handler(minishell, arg, buf + i_end, quote_type);
		}
		i_start = i_end;
	}
}
