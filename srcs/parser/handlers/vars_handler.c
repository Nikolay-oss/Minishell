/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkenchur <dkenchur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 20:50:18 by dkenchur          #+#    #+#             */
/*   Updated: 2021/07/13 20:50:19 by dkenchur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parser.h"

static void	special_cases_handler(t_minishell *minishell, t_node **node)
{
	char	*var;

	var = (char *)(*node)->content;
	if (ft_strcmp(var, "$") && *var == '$')
	{
		free((*node)->content);
		(*node)->content = NULL;
	}
}

static void	swap_nametovalue(t_minishell *minishell, t_list **str_parts)
{
	t_node	*node;
	char	*var;
	char	*tmp;

	node = (*str_parts)->head;
	while (node)
	{
		if (*(char *)node->content == '$')
		{
			if (!search_var_value(minishell, &var, node))
				return ;
			if (var)
			{
				tmp = (char *)node->content;
				node->content = (void *)var;
				free(tmp);
			}
			else
				special_cases_handler(minishell, &node);
		}
		node = node->next;
	}
}

static t_uint	skip_varname(char *str, t_uint end)
{
	t_bool	num_flag;

	if (*(str + end) == '?')
	{
		end++;
	}
	else
	{
		num_flag = 0;
		while (*(str + end))
		{
			if (ft_isalpha(*(str + end)) || *(str + end) == '_')
				num_flag = 1;
			else if (!num_flag && ft_isdigit(*(str + end)))
				return (++end);
			else if (!ft_isalnum(*(str + end)) && *(str + end) != '_')
				return (end);
			end++;
		}
	}
	return (end);
}

static void	split_str_into_vars(t_minishell *minishell, t_list **str_parts,
	char *str)
{
	t_uint	start;
	t_uint	end;
	char	*p_var;
	char	*str_part;

	init_vars_in_split_into_vars(&str_part, &start, &end);
	p_var = ft_strchr(str, '$');
	while (p_var)
	{
		start = (t_uint)(end + (p_var - (str + end)));
		str_part = ft_substr(str, end, start - end);
		if (!str_part)
			break ;
		ft_push_back(*str_parts, str_part);
		end = skip_varname(str, ++start);
		str_part = ft_substr(str, start - 1, end - (start - 1));
		if (!str_part)
			break ;
		ft_push_back(*str_parts, str_part);
		p_var = ft_strchr(++p_var, '$');
	}
	if (!str_part)
		ft_malloc_error(minishell);
	else
		check_last_var(minishell, str_parts, str, end);
}

char	*get_str_withvars(t_minishell *minishell, char *str)
{
	t_list	*str_parts;
	char	*new_arg;

	str_parts = ft_create_lst();
	if (!check_memory(minishell, (void *)str_parts))
		return (NULL);
	split_str_into_vars(minishell, &str_parts, str);
	if (minishell->ismem_error)
		return (NULL);
	if (!str_parts->head)
	{
		ft_lst_clear(&str_parts, &free);
		return (NULL);
	}
	swap_nametovalue(minishell, &str_parts);
	if (minishell->ismem_error)
		return (NULL);
	new_arg = ft_lst_to_str(str_parts);
	ft_lst_clear(&str_parts, &free);
	check_memory(minishell, (void *)new_arg);
	return (new_arg);
}
