#include "minishell.h"

static	int	ft_is_env(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (1);
	else if (c >= 'a' && c <= 'z')
		return (1);
	else if (c == '_')
		return (1);
	else
		return (0);
}

static	int	ft_un_parser(char *var)
{
	int i;

	i = 0;
	while (var[i])
	{
		if(ft_is_env(var[i]))
			i++;
		else
			return (0);
	}
	return (1);
}

void	ft_unset(t_minishell *minishell, char **var)
{
	t_node	*node;
	int 	i;

	i = 1;
	printf("node: |%s|\n", minishell->old_pwd);
	if(ft_un_parser(var[i]))
	{
		node = getvar_node(minishell->env, var[i]);
		if (!strcmp(var[i], "OLDPWD") && node)
		{
			minishell->old_pwd = ft_strdup((char *)node->content);
			printf("old pwd - |%s|\n", minishell->old_pwd);
		}
		if (!strcmp(var[i], "PWD") && node)
		{
			minishell->pwd = ft_strdup((char *)node->content);
		}
		if (node) //&& strcmp(var[i], "OLDPWD") != 0)
		{
			ft_del_node(minishell->env, &free, node);
		}
		write(1, "222\n", 4);
	}
	else
		printf("unset: %s not a valid identifier\n", var[i]);
	i++;
	printf("node: |%s|\n", minishell->old_pwd);
	while (var[i])
	{
//		printf("var: |%s|\n", var[i]);
		// printf("node12: |%s|\n", (char *)node->content);

		if(ft_un_parser(var[i]))
		{
			node = getvar_node(minishell->env, var[i]);
			if (node)
				ft_del_node(minishell->env, &free, node);
		}
		else
			printf("unset: %s not a valid identifier\n", var[i]);
		i++;
	}
//	if (!node && var[i])
//		printf("unset: %s not a valid identifier\n", var[i]);
}
