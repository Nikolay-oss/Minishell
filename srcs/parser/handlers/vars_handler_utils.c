#include "ft_parser.h"

void	search_var_value(t_minishell *minishell, char **var, t_node *node)
{
	if (!ft_strcmp(node->content, "$?"))
		*var = ft_itoa(minishell->exit_status);
	else
	{
		*var = getvar_value(minishell->env, (char *)(node->content) + 1);
		if (!*var)
			*var = getvar_value(minishell->hide_vars, (char *)(node->content) + 1);
	}
}

char	*tilda_handler(t_minishell *minishell, char *str)
{
	char	*home_path;
	t_uint	i;

	home_path = NULL;
	i = 0;
	if (*str == '=')
		i++;
	if (ft_memchr(" /", *(str + i + 1), 3))
	{
		if (*str == '=')
			home_path = ft_strjoin("=", minishell->home_path);
		else
			home_path = ft_strdup(minishell->home_path);
		if (!home_path)
			return (NULL); // error
	}
	return (home_path);
}