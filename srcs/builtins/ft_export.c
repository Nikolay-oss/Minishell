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

static int	add_to_vars(t_list *vars, t_node **var_node, char *var)
{
	char	*new_var;

	new_var = ft_strdup(var);
	if (!new_var)
		return (1);
	if (var_node && *var_node)
	{
		free((*var_node)->content);
		(*var_node)->content = (void *)new_var;
	}
	else
		ft_push_back(vars, new_var);
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

static int	add_var(t_minishell *minishell, char *var, t_uint var_type)
{
	t_node	*envvar_node;
	char	*var_name;
	int		errorcode;

	errorcode = 0;
	var_name = getvar_name(var, var_type);
	if (!var_name)
		return (1);
	envvar_node = getvar_node(minishell->env, var_name);
	if (var_type == 1)
		errorcode = add_to_vars(minishell->env, &envvar_node, var);
	else if (var_type == 2)
		errorcode = add_to_vars(minishell->env_secret, NULL, var);
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
		}
		i++;
	}
	return (errorcode);
}
