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

static t_bool	check_last_arg(t_minishell *minishell, char *buf, int *flag)
{
	t_bool	isvar;

	isvar = 0;
	if (*buf == '_' && *(buf + 1) == '=')
		isvar = 0;
	else if (minishell->all_commands->size == 0)
	{
		isvar = 1;
		*flag = 2;
	}
	else if (ispipe(*(char *)minishell->all_commands->tail->content))
	{
		isvar = 1;
		*flag = 3;
	}
	else if (*(int *)minishell->f_quotes->tail->content == 2)
	{
		isvar = 1;
		*flag = 2;
	}
	return (isvar);
}

void	change_hide_var_flag(t_minishell *minishell, char *buf, int *flag)
{
	char	*p_equal;
	int		flag_new;

	flag_new = -1;
	p_equal = ft_strchr(buf, '=');
	if (!p_equal || !check_last_arg(minishell, buf, &flag_new))
		return ;
	if (var_parser(buf))
	{
		minishell->hide_vars_count++;
		*flag = flag_new;
	}
}

t_uint	add_to_hide_vars(t_minishell *minishell, t_commands *cmd, int var_type)
{
	t_uint	i;
	char	*hide_var;

	i = 0;
	while (*(cmd->cmd + i))
	{
		if (*(cmd->flags_quotes + i) == var_type)
		{
			hide_var = ft_strdup(*(cmd->cmd + i));
			if (!hide_var)
			{
				minishell->exit_status = errno;
				return (0);
			}
			ft_push_back(minishell->hide_vars, hide_var);
		}
		else
			return (i);
		i++;
	}
	return (0);
}
