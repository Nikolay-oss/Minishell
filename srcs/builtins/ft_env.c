/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkenchur <dkenchur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 21:24:04 by dkenchur          #+#    #+#             */
/*   Updated: 2021/07/13 21:24:05 by dkenchur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		printf("node ->%s\n", (char *)current->content);
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

char	*getvar_value(t_minishell *shell, t_list *vars, const char *var_name)
{
	t_node	*node_var;
	char	*var_value;

	node_var = getvar_node(vars, var_name);
	if (!node_var)
		return (NULL);
	var_value = ft_strdup(ft_strchr(node_var->content, '=') + 1);
	if (!var_value)
		ft_malloc_error(shell);
	return (var_value);
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
