#include "minishell.h"

void ft_cd_handler(char **buf, t_node *node, t_node *node_old, t_list *env)
{
	(*buf) = getcwd(NULL, PATH_MAX);
	node_old = getvar_node(env, "OLDPWD");
	if(node_old)
	{
		free(node_old->content);
		node->content = ft_strrchr((node->content), '=');
		(node->content)++;
		node_old->content = (void *)ft_strjoin("OLDPWD=", node->content);
	}
	node->content = (void *)ft_strjoin("PWD=", (*buf));
}

void	ft_cd(t_list *env, char *path)
{
	int		res;
	char	*buf;
	t_node	*node;
	t_node	*node_old;

	if (!path || !strcmp(path, "~"))
	{
		path = getvar_node(env, "HOME")->content;
		path = ft_strrchr(path, '=');
		path++;
	}
	res = chdir(path);
	node = getvar_node(env, "PWD");
	if(res < 0)
		printf("cd: %s: %s\n", strerror(errno), path);
	else
	{
		ft_cd_handler(&buf, node, node_old, env);
		printf("%s\n", buf);
		free(buf);
	}
}
