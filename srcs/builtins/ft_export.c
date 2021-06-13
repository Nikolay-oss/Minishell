#include "minishell.h"
#include "data_types.h"

/*
	work only -> export var_name=value
	rewrite!!!
*/

void	ft_export(t_list **env, char *env_variable)
{
	t_node	*variable_node;
	char	*variable_name;
	char	*p_equal;
	char	*new_variable;
	t_uint	size;

	if (!env_variable)
		return ;
	p_equal = ft_strchr(env_variable, '=');
	if (!p_equal)
		return ;
	size = (t_uint)(p_equal - env_variable);
	variable_name = ft_substr(env_variable, 0, size);
	variable_node = getenv_node(*env, variable_name);
	new_variable = ft_strdup(env_variable);
	if (variable_node)
	{
		free(variable_node->content);
		variable_node->content = new_variable;
	}
	else
		ft_push_back(*env, new_variable);
	free(variable_name);
}
