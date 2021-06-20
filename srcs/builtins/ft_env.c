#include "minishell.h"

t_node	*getvar_node(t_list *vars, const char *var_name)
{
	t_node	*current;
	size_t	size;
	char	*p_equal;
	char	*tmp;

	if (!vars)
		return (NULL);
	current = vars->head;
	size = 0;
	while (current)
	{
		p_equal = ft_strchr((char *)current->content, '=');
		if (p_equal)
		{
			size = (size_t)(p_equal - (char *)current->content);
			if (!ft_memcmp(current->content, var_name, size))
				return (current);
		}
		current = current->next;
	}
	return (NULL);
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

void	ft_env(t_list *env)
{
	t_node	*current;

	current = env->head;
	while (current)
	{
		ft_putendl_fd(current->content, 1);
		current = current->next;
	}
}
