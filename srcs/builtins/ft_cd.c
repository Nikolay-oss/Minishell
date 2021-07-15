#include "minishell.h"

void	ft_cd_handler(char **buf, t_node *node, t_node *node_old, t_list *env)
{
	int		i;

	(*buf) = getcwd(NULL, PATH_MAX); 							// protect
	if (!(*buf))
	{
		print_error("getcwd", errno);
		signals.exit_status = 1;
		return ;
	}
	node_old = getvar_node(env, "OLDPWD");
	if (!node_old)
	{
		ft_push_back(env, ft_strjoin("OLDPWD=",
									 getcwd(NULL, PATH_MAX)));
		node_old = getvar_node(env, "OLDPWD");
	}
	free(node_old->content);
	i = ft_get_index_symbol(node->content, '=');
	node_old->content = (void *)ft_strjoin("OLDPWD=", (node->content + ++i)); // free
	free(node->content);
	node->content = (void *)ft_strjoin("PWD=", (*buf));  // edit
	free((*buf));
	signals.exit_status = 0;
}

void	ft_cd(t_minishell *minishell, char *path)
{
	int		res;
	char	*buf;
	t_node	*node;
	t_node *node_old;

	if (!path || !ft_strcmp(path, "~"))
		path = minishell->home_path;
	else if (!ft_strcmp(path, "-"))
	{

	}
	res = chdir(path);
	node = getvar_node(minishell->env, "PWD");
	if (!node)
	{
		write(2, "lalal\n", 6);
		buf = getcwd(NULL, PATH_MAX);
		ft_push_back(minishell->env, ft_strjoin("PWD=", buf)); 					//free getcwd
		node = getvar_node(minishell->env, "PWD");
		free(buf);
	}
	if(res < 0 && (ft_strcmp(path, "-") > 0 || ft_strcmp(path, "_") < 0))
		printf("cd: %s: %s\n", strerror(errno), path);
	else if (!ft_strcmp(path, "-"))
	{
//		ft_cd_swap
	}
	else
	{
		printf("hey\n");
		write(1, "123\n", 4);
		ft_cd_handler(&buf, node, node_old, (minishell->env));
	}
}
