#include "ft_parser.h"

static t_bool	shlvl_handler(t_minishell *minishell)
{
	t_node	*node_shlvl;
	char	*new_shlvl;
	char	*tmp;
	int		shlvl;

	node_shlvl = getvar_node(minishell->env, "SHLVL");
	if (node_shlvl)
	{
		shlvl = (int)ft_atoi((char *)node_shlvl->content + 6);
		tmp = ft_itoa(++shlvl);
		new_shlvl = ft_strjoin("SHLVL=", tmp);
		free(tmp);
	}
	else
	{
		new_shlvl = ft_strdup("SHLVL=1");
	}
	if (!new_shlvl)
	{
		ft_malloc_error(minishell);
		return (0);
	}
	free(node_shlvl->content);
	node_shlvl->content = (char *)new_shlvl;
	return (1);
}

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
	return (shlvl_handler(minishell));
}

static void	t_signals_init()
{
	signals.pid = 0;
	// signals.sig_int = 0;
	// signals.sig_quit = 0;
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
	// signals.sig_int = 0; // 3
	// signals.sig_quit = 0; // 4
	minishell->old_pwd = 0;
	minishell->pwd = 0;
	minishell->cursor_pos = 0;
	// get pwd
	node = getvar_node(minishell->env, "PWD");
	if(!node)
	{
		buf = getcwd(NULL, PATH_MAX);
		minishell->pwd = strdup(buf);
		ft_push_back(minishell->env,
					 ft_strjoin("PWD=", buf));
		free(buf);
	}
//	minishell->home_path = getvar_value(minishell, minishell->env, "HOME");
	if (minishell->ismem_error)
		return (0);
	minishell->env_secret = ft_create_lst();
	if (!check_memory(minishell, (void *)minishell->env_secret))
		return (0);
	return (1);
}
