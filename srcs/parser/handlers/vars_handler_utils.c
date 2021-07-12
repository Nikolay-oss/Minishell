#include "ft_parser.h"

t_bool	search_var_value(t_minishell *minishell, char **var, t_node *node)
{
	if (!ft_strcmp(node->content, "$?"))
	{
		*var = ft_itoa(minishell->exit_status);
	}
	else
	{
		*var = getvar_value(minishell, minishell->env,
			(char *)(node->content) + 1);
	}
	if (minishell->ismem_error)
		return (0);
	return (1);
}

char	*tilda_handler(t_minishell *minishell, char *str)
{
	char	*home_path;
	t_uint	i;

	if (!minishell->home_path)
		return (ft_strdup(""));
	home_path = NULL;
	i = 0;
	if (*str == '=')
		i++;
	if (ft_memchr(" /", *(str + i + 1), 3))
	{
		if (*str == '=')
			home_path = ft_strjoin("=", minishell->home_path);
		else
			home_path = ft_strdup(minishell->home_path);
		if (!home_path)
		{
			ft_malloc_error(minishell);
			return (NULL);
		}
	}
	return (home_path);
}

void	check_last_var(t_minishell *minishell, t_list **str_parts, char *str,
	t_uint end)
{
	char	*str_part;

	str_part = NULL;
	if (*(str + end) && !ft_strchr(str + end, '$'))
	{
		str_part = ft_substr(str, end, (size_t)(ft_strchr(str + end, 0) - end));
		if (!str_part)
		{
			ft_malloc_error(minishell);
			return ;
		}
		ft_push_back(*str_parts, str_part);
	}
}

void	init_vars_in_split_into_vars(char **str, t_uint *start, t_uint *end)
{
	*str = "";
	init_range(start, end, 0, 0);
}
