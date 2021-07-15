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

void	ft_unset(t_list *env, char **var)
{
	t_node	*node;
	int 	i;

	i = 1;
	node = getvar_node(env, var[i]);
//	write(1, "HHHHHHH\n", 8);
//	printf("var1: |%s|\n", var[i]);
//	printf("node1: |%s|\n", node);
//	if (ft_strcmp(ft_un_parser(var), "(null)"));
//	printf("parser1: |%d|\n", ft_un_parser(var[i]));
	if(ft_un_parser(var[i]))
	{
		node = getvar_node(env, var[i]);
		if (node)
			ft_del_node(&env, free, node);
	}
	else
		printf("unset: %s not a valid identifier\n", var[i]);
//	printf("var2: |%s|\n", var[i]);
//	printf("node2: |%s|\n", node);
//	if (ft_strcmp(ft_un_parser(var), "(null)"));
//	printf("parser2: |%d|\n", ft_un_parser(var[i]));
	i++;
	while (var[i])
	{
//		printf("var: |%s|\n", var[i]);
//		printf("node: |%s|\n", node);

		if(ft_un_parser(var[i]))
		{
			node = getvar_node(env, var[i]);
			if (node)
				ft_del_node(&env, free, node);
		}
		else
			printf("unset: %s not a valid identifier\n", var[i]);
		i++;
	}
//	if (!node && var[i])
//		printf("unset: %s not a valid identifier\n", var[i]);
}
