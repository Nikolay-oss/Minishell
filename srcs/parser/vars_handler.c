#include "ft_parser.h"

// обработать ошибки
// можно переделать!
char	*add_var_to_str(char **str, char *var_value, t_uint start, t_uint end)
{
	char	*newstr;
	char	*tmp;
	char	buf;

	buf = *(*str + start);
	*(*str + start) = 0;
	newstr = ft_strjoin(*str, var_value);
	tmp = newstr;
	*(*str + start) = buf;
	newstr = ft_strjoin(newstr, *str + end);
	free(*str);
	free(tmp);
	*str = NULL;
	return (newstr);
}

char	*insert_vars_in_str(t_minishell *minishell, t_list **vars, char *str)
{
	char	*var;
	char	*var_value;
	t_node	*node;
	t_uint	var_size;
	char	*newstr;

	node = (*vars)->head;
	newstr = ft_strdup(str);
	free(str);
	while (node)
	{
		var_size = ft_strlen(node->content);
		var = ft_strnstr(newstr, node->content, 4096);
		if (var)
		{
			var_value = getvar_value(minishell->env, node->content + 1);
			if (var_value)
				newstr = add_var_to_str(&newstr, var_value, var - newstr,
					(var - newstr) + var_size);
			else
				newstr = add_var_to_str(&newstr, "", var - newstr,
					(var - newstr) + var_size);
		}
		node = node->next;
	}
	ft_lst_clear(*vars, &free);
	return (newstr);
}

char	*get_str_withvars(t_minishell *minishell, char *str)
{
	t_list	*vars;
	t_uint	i;
	t_uint	var_start;
	char	chr_end_var;
	char	*var_name;

	i = 0;
	vars = ft_create_lst();
	while (*(str + i))
	{
		if (*(str + i) == '$')
		{
			var_start = (++i) - 1;
			while (ft_isalpha(*(str + i)))
				i++;
			if (ft_isalpha(*(str + i - 1)))
			{
				chr_end_var = *(str + i);
				*(str + i) = 0;
				var_name = ft_strdup(str + var_start);
				if (!var_name)
					return (NULL); // error
				ft_push_back(vars, var_name);
				*(str + i) = chr_end_var;
			}
		}
		if (*(str + i) && *(str + i) != '$')
			i++;
	}
	return (insert_vars_in_str(minishell, &vars, str));
}
