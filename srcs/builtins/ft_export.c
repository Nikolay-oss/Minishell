#include "minishell.h"
/*
	дописать под PATH
*/
static t_uint	var_parser(char *var, int *errorcode)
{
	t_uint	var_type;

	var_type = 0;
	if (!ft_isalpha(*var))
	{
		printf("minishell: export: '%s': not a valid identifier\n", var);
		*errorcode = 1;
	}
	else if (ft_strchr(var, '='))
		var_type = 1;
	else
		var_type = 2;
	return (var_type);
}

static int	add_to_env(t_list *env, t_node **envvar_node, char *var)
{
	char	*new_var;

	new_var = ft_strdup(var);
	if (!new_var)
		return (1);
	if (*envvar_node)
	{
		free((*envvar_node)->content);
		(*envvar_node)->content = (void *)new_var;
	}
	else
		ft_push_back(env, new_var);
	return (0);
}

static char	*getvar_name(char *var, t_uint var_type)
{
	char	*var_name;
	t_uint	name_size;

	name_size = 0;
	if (var_type == 2)
		var_name = var;
	else
	{
		name_size = (t_uint)(ft_strchr(var, '=') - var);
		var_name = ft_substr(var, 0, name_size);
		if (!var_name)
			return (NULL); // error
	}
	return (var_name);
}

static int	add_var(t_list *env, t_list *hide_vars, char *var, t_uint var_type)
{
	t_node	*hidevar_node;
	t_node	*envvar_node;
	char	*var_name;
	int		errorcode;

	errorcode = 0;
	var_name = getvar_name(var, var_type);
	if (!var_name)
		return (1);
	hidevar_node = getvar_node(hide_vars, var_name);
	envvar_node = getvar_node(env, var_name);
	if (var_type == 1)
		errorcode = add_to_env(env, &envvar_node, var);
	else if (hidevar_node && var_type == 2)
	{
		errorcode = add_to_env(env, &envvar_node, hidevar_node->content);
		ft_del_node(hide_vars, &free, hidevar_node);
	}
	return (errorcode);
}

int	ft_export(t_minishell *minishell, char **vars)
{
	t_uint	i;
	t_uint	var_type;
	int		errorcode;

	i = 0;
	errorcode = 0;
	while (*(vars + i))
	{
		var_type = var_parser(*(vars + i), &errorcode);
		if (var_type)
		{
			if (add_var(minishell->env, minishell->hide_vars, *(vars + i),
				var_type) == 1)
			{
				errorcode = 1;
			}
		}
		i++;
	}
	return (errorcode);
}
