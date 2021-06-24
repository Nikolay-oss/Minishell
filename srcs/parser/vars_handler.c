#include "ft_parser.h"

t_bool	save_var(t_minishell *minishell, t_list **vars, char *var_name)
{
	char	*var_value;
	int		*notfound;

	var_value = getvar_value(minishell->env, var_name);
	if (!var_value)
		var_value = getvar_value(minishell->hide_vars, var_name);
	if (var_value)
		ft_push_back(*vars, var_value);
	// else
	// {
	// 	notfound = (int *)malloc(sizeof(int));
	// 	*notfound = 404;
	// 	if (notfound)
	// 		ft_push_back(*vars, notfound);
	// }
}

void	swap_substrs(t_list *substrs, char **dst, char *src, t_uint src_size)
{
	t_uint	i;
	t_uint	j;
	t_node	*node;

	node = substrs->head;
	i = 0;
	j = 0;
	while (j < src_size)
	{
		if (*(src + j) == '$')
		{
			i += ft_strlcpy(*dst + i, node->content, ft_strlen(node->content) + 1);
			j++;
			while (ft_isalpha(*(src + j)) && !ft_memchr(" =$", *(src + j), 3))
				j++;
			node = node->next;
		}
		*(*dst + i) = *(src + j);
		j++;
		i++;
	}
}

char	*insert_vars_in_str(t_list *vars, char *cmd_str, t_uint sizenovars)
{
	char	*strnew;
	t_uint	strnew_size;
	t_node	*node_var;

	node_var = vars->head;
	strnew_size = sizenovars;
	while (node_var)
	{
		strnew_size += ft_strlen((const char *)node_var->content);
		node_var = node_var->next;
	}
	strnew = (char *)ft_calloc(strnew_size + 1, sizeof(char));
	if (!strnew)
		return (NULL); // error
	swap_substrs(vars, &strnew, cmd_str, ft_strlen(cmd_str));
	return (strnew);
}



// char	*insert_var_in_str(t_minishell *minishell, char	*str)
// {
// 	char	end_var;
// 	char	*str_var;
// 	t_node	*var_node;
// 	t_uint	dollar_pos;
// 	t_uint	i;

// 	i = -1;
// 	while (*(str + i))
// 	{
// 		i++;
// 		if (*(str + i) == '$')
// 		{
// 			dollar_pos = i;
// 			while (*(str + i) && *(str + i) != ' ')
// 				i++;
// 			end_var = *(str + i);
// 			*(str + i) = 0;
// 			var_node = getvar_node(minishell->env, str + dollar_pos + 1);
// 			if (!var_node)
// 				var_node = getvar_node(minishell->hide_vars, str + dollar_pos + 1);
// 			if (!var_node)
// 				continue ;
// 			else
// 				; // insert var
// 		}
// 	}
// }