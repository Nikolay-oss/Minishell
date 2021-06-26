#include "ft_parser.h"

void	search_var_value(t_minishell *minishell, char **var, t_node *node)
{
	if (!ft_strcmp(node->content, "$?"))
		*var = ft_itoa(minishell->exitcode_last);
	else
	{
		*var = getvar_value(minishell->env, (char *)(node->content) + 1);
		if (!*var)
			*var = getvar_value(minishell->hide_vars, (char *)(node->content) + 1);
	}
}

void	tilda_handler(t_minishell *minishell, void **str)
{
	if (!ft_strcmp(*str, "~"))
	{
		free(*str);
		*str = (void *)getvar_value(minishell->env, "HOME");
		if (!*str)
			; // error
	}
}
