#include "ft_parser.h"

extern	t_signal	signals;

static t_bool	init_env(t_minishell *minishell, char **envp)
{
	t_uint	i;
	char	*env_variable;

	minishell->env = ft_create_lst();
	if (!check_memory(minishell, (void *)minishell->env))
		return (0);
	i = 0;
	while (*(envp + i))
	{
		env_variable = ft_strdup(*(envp + i));
		if (!check_memory(minishell, (void *)env_variable))
			return (0);
		ft_push_back(minishell->env, env_variable);
		i++;
	}
	return (1);
}

t_bool	init_shell(t_minishell *minishell, char **envp)
{
	if (!init_env(minishell, envp))
		return (0);
	minishell->exit_status = (long long int)NULL; // 1
	minishell->home_path = (char *)NULL; // 2
	signals.sig_int = 0; // 3
	signals.sig_quit = 0; // 4
	minishell->home_path = getvar_value(minishell, minishell->env, "HOME");
	if (!check_memory(minishell, (void *)minishell->home_path))
		return (0);
	minishell->env_secret = ft_create_lst();
	if (!check_memory(minishell, (void *)minishell->env_secret))
		return (0);
	return (1);
}
