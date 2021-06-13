#include "minishell.h"
#include "data_types.h"

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
