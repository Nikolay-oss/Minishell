/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkenchur <dkenchur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 21:24:09 by dkenchur          #+#    #+#             */
/*   Updated: 2021/07/15 05:25:22 by dkenchur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_uint	check_var(char *var, int *errorcode)
{
	t_uint	var_type;

	var_type = 0;
	if (!var_parser(var))
	{
		ft_putstr_fd("minishell: export: '", 2);
		ft_putstr_fd(var, 2);
		ft_putendl_fd("': not a valid identifier", 2);
		*errorcode = 1;
	}
	else if (ft_strchr(var, '='))
		var_type = 1;
	else
		var_type = 2;
	return (var_type);
}

static int	add_to_vars(t_minishell *minishell, t_list *vars,
	t_node **var_node, char *var)
{
	char	*new_var;
	char	*tmp;

	tmp = NULL;
	new_var = ft_strdup(var);
	if (!new_var)
	{
		ft_malloc_error(minishell);
		return (errno);
	}
	if (var_node && *var_node)
	{
		free((*var_node)->content);
		(*var_node)->content = (void *)new_var;
	}
	else
	{
		tmp = (char *)vars->tail->content;
		vars->tail->content = (void *)new_var;
		ft_push_back(vars, tmp);
	}
	return (0);
}

int	add_var(t_minishell *minishell, char *var, t_uint var_type)
{
	t_node	*envvar_node;
	int		errorcode;
	char	*p_equal;

	errorcode = 0;
	p_equal = ft_strchr(var, '=');
	if (p_equal)
		*p_equal = 0;
	if (!ft_strcmp(var, "_"))
		return (errorcode);
	envvar_node = getvar_node(minishell->env, var);
	if (p_equal)
		*p_equal = '=';
	if (var_type == 1)
		errorcode = add_to_vars(minishell, minishell->env, &envvar_node, var);
	else if (var_type == 2)
		errorcode = add_to_vars(minishell, minishell->env_secret, NULL, var);
	return (errorcode);
}

int	ft_export(t_minishell *minishell, char **vars)
{
	t_uint	i;
	t_uint	var_type;
	int		errorcode;

	i = 0;
	errorcode = 0;
	if (!*vars)
		errorcode = print_declare_env(minishell);
	while (*(vars + i))
	{
		var_type = check_var(*(vars + i), &errorcode);
		if (var_type)
		{
			if (add_var(minishell, *(vars + i), var_type) == 1)
				errorcode = 1;
			else if (minishell->ismem_error)
				return (errno);
		}
		i++;
	}
	return (errorcode);
}
