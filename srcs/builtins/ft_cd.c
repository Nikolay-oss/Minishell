#include "minishell.h"

void	ft_cd(t_list *env, char *path)
{
	int res;
	char *buf;
	struct s_node *node;
	struct s_node *node_old;

	if (!path || !strcmp(path, "~"))
	{
		path = getvar_node(env, "HOME")->content;
		path = ft_strrchr(path, '=');
		path++;
	}
	res = chdir(path);
	node = getvar_node(env, "PWD");
	if(res < 0)
		printf("Error: %s\n", strerror(errno));
	else
	{
		buf = getcwd(NULL, PATH_MAX);
//		printf("->|%s|\n", buf);
//		printf("---content: %s\n", (char *)node->content);
		node_old = getvar_node(env, "OLDPWD");
//		printf("lllllllllllllll\n");
		if(node_old)
			node_old->content = (void *)ft_strdup(node->content);
		if (node && node->content)
			free(node->content);
		node->content = (void *)ft_strjoin("PWD=", buf);
		printf("%s\n", buf);
		free(buf);
	}
}
