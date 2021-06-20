#include "minishell.h"

void	ft_unset(t_list *env, char *var)
{
	t_node	*node;

	node = getvar_node(env, var);
	if (node)
		ft_del_node(env, free, node);
	else
		printf("unset: %s invalid parameter name\n", var);
}
