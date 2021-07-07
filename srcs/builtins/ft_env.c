#include "minishell.h"

t_node	*getvar_node(t_list *vars, const char *var_name)
{
	t_node	*current;
	char	*p_equal;
	char	*tmp;
	char	buf;

	if (!vars)
		return (NULL);
	current = vars->head;
	while (current)
	{
		p_equal = ft_strchr((char *)current->content, '=');
		if (p_equal)
		{
			buf = *p_equal;
			*p_equal = 0;
			if (!ft_strcmp(var_name, current->content))
			{
				*p_equal = buf;
				return (current);
			}
			*p_equal = buf;
		}
		current = current->next;
	}
	return (NULL);
}

char	*getvar_value(t_list *vars, const char *var_name)
{
	t_node	*node_var;
	char	*var_value;

	node_var = getvar_node(vars, var_name);
	if (!node_var)
		return (NULL);
	var_value = ft_strdup(ft_strchr(node_var->content, '=') + 1);
	if (!var_value)
		return (NULL); // error
	return (var_value);
}

void	init_env(t_list **env, char **envp)
{
	t_uint	i;
	char	*env_variable;

	*env = ft_create_lst();
	if (!*env)
		; // error
	i = 0;
	while (*(envp + i))
	{
		env_variable = ft_strdup(*(envp + i));
		if (!env_variable)
			; // errror
		ft_push_back(*env, env_variable);
		i++;
	}
}

int	ft_env(t_list *env)
{
	t_node	*current;

	current = env->head;
	while (current)
	{
		ft_putendl_fd(current->content, 1);
		current = current->next;
	}
	return (0);
}
