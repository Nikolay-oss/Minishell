#include "ft_parser.h"

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
		if (ft_strnstr(env_variable, "SHLVL=", 100))
			(*(env_variable + 6))++;
		ft_push_back(minishell->env, env_variable);
		i++;
	}
	return (1);
}

static void	t_signals_init()
{
	signals.pid = 0;
	signals.sig_int = 0;
	signals.sig_quit = 0;
	signals.exit_status = 0;
}

t_bool	init_shell(t_minishell *minishell, char **envp)
{
	t_node	*node;
	char *buf;

	t_signals_init();
	if (!init_env(minishell, envp))
		return (0);
	minishell->exit_status = (long long int)NULL; // 1
	minishell->home_path = (char *)NULL; // 2
	signals.sig_int = 0; // 3
	signals.sig_quit = 0; // 4
	// get pwd
	node = getvar_node(minishell->env, "PWD");
	if(!node)
	{
		buf = getcwd(NULL, PATH_MAX);
		ft_push_back(minishell->env,
					 ft_strjoin("PWD=", buf)); //free getcwd
		free(buf);
	}
	minishell->home_path = getvar_value(minishell, minishell->env, "HOME");
	if (minishell->ismem_error)
		return (0);
	minishell->env_secret = ft_create_lst();
	if (!check_memory(minishell, (void *)minishell->env_secret))
		return (0);
	return (1);
}
