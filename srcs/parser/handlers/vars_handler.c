#include "ft_parser.h"

#define DEBUG

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
			search_var_value(minishell, &var, node);
			if (var)
			{
				tmp = (char *)node->content;
				node->content = (void *)ft_strdup(var);
				free(tmp);
				if (!node->content)
					return ; // error
			}
			else
				special_cases_handler(minishell, &node);
		}
		node = node->next;
	}
}

static t_uint	skip_varname(char *str, t_uint end)
{
	if (*(str + end) == '?')
		end++;
	else
	{
		while (ft_isalpha(*(str + end)))
			end++;
	}
	return (end);
}

static void	split_str_into_vars(t_list **str_parts, char *str)
{
	t_uint	start;
	t_uint	end;
	char	*var;
	char	*str_part;

	start = 0;
	end = 0;
	var = ft_strchr(str, '$');
	while (var)
	{
		start = (t_uint)(end + (var - (str + end)));
		str_part = ft_substr(str, end, start - end);
		ft_push_back(*str_parts, check_memory(&str_part));
		end = ++start;
		end = skip_varname(str, end);
		str_part = ft_substr(str, start - 1, end - (start - 1));
		ft_push_back(*str_parts, check_memory(&str_part));
		var = ft_strchr(++var, '$');
	}
	if (*(str + end) && !ft_strchr(str + end, '$'))
	{
		str_part = ft_substr(str, end, (size_t)(ft_strchr(str + end, 0) - end));
		ft_push_back(*str_parts, check_memory(&str_part));
	}
}

char	*get_str_withvars(t_minishell *minishell, char *str)
{
	t_list	*str_parts;
	char	*new_arg;

	str_parts = ft_create_lst();
	split_str_into_vars(&str_parts, str);
	if (!str_parts->head)
	{
		ft_lst_clear(str_parts, &free);
		return (NULL);
	}
	swap_nametovalue(minishell, &str_parts);
	new_arg = ft_lst_to_str(str_parts);
	#ifndef DEBUG
		t_node *node;

		node = str_parts->head;
		while (node)
		{
			printf("|%s|\n", (char *)node->content);
			node = node->next;
		}
	#endif
	ft_lst_clear(str_parts, &free);
	if (new_arg)
		return (new_arg);
	else
		return (NULL); // error
}
