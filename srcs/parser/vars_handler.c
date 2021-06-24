#include "ft_parser.h"

#define DEBUG

void	search_var_value(t_minishell *minishell, char **var, t_node *node)
{
	*var = getvar_value(minishell->env, (char *)(node->content) + 1);
	if (!*var)
		*var = getvar_value(minishell->hide_vars, (char *)(node->content) + 1);
}

void	special_cases_handler(t_minishell *minishell, t_node **node)
{
	char	*var;
	// char	*new_var;

	var = (char *)(*node)->content;
	// if (!ft_strcmp(var, "~"))
	// {
	// 	free((*node)->content);
	// 	(*node)->content = getvar_value(minishell->env, "HOME");
	// }
	if (ft_strcmp(var, "$"))
	{
		free((*node)->content);
		(*node)->content = NULL;
	}
}

void	swap_nametovalue(t_minishell *minishell, t_list **str_parts)
{
	t_node	*node;
	char	*var;
	char	*tmp;

	node = (*str_parts)->head;
	while (node)
	{
		if (*(char *)node->content == '$') // || *(char *)node->content == '~')
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

void	split_str(t_list **str_parts, char *str)
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
		while (ft_isalpha(*(str + end)))
			end++;
		str_part = ft_substr(str, start, end - --start);
		ft_push_back(*str_parts, check_memory(&str_part));
		var = ft_strchr(++var, '$');
	}
	if (*(str + end) && !ft_strchr(str + end, '$'))
	{
		str_part = ft_substr(str, end, (size_t)(ft_strchr(str + end, 0) - end));
		ft_push_back(*str_parts, check_memory(&str_part));
	}
}

void	set_str_withvars(t_minishell *minishell, char *str)
{
	t_list	*str_parts;
	char	*new_arg;

	str_parts = ft_create_lst();
	split_str(&str_parts, str);
	if (!str_parts->head)
		return ;
	swap_nametovalue(minishell, &str_parts);
	new_arg = ft_lst_to_str(str_parts);
	if (new_arg)
	{
		free(minishell->commands->tail->content);
		minishell->commands->tail->content = (void *)new_arg;
	}
	else
		; // error
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
}
