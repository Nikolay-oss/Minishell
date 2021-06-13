#include "minishell.h"
#include "data_types.h"

t_node	*getenv_node(t_list *env, const char *env_variable)
{
	t_node	*current;
	t_uint	size;
	char	*p_equal;
	char	*tmp;

	current = env->head;
	size = 0;
	while (current)
	{
		p_equal = ft_strchr((char *)current->content, '=');
		if (p_equal)
		{
			size = (t_uint)(p_equal - (char *)current->content);
			tmp = ft_substr((char *)current->content, 0, size);
			if (!tmp)
				; // error
			if (!ft_strncmp(tmp, env_variable, size))
			{
				free(tmp);
				return (current);
			}
			free(tmp);
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
		ft_push_back(*env, (void *)env_variable);
		i++;
	}
}

void	ft_env(t_list *env)
{
	t_node	*current;

	current = env->head;
	while (current)
	{
		ft_putendl_fd((char *)current->content, 1);
		current = current->next;
	}
}
