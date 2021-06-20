#include "minishell.h"

void	ft_cd(t_list *env, char *path)
{
	int res;
	char *buf;
	struct s_node *node;
	struct s_node *node_old;

	if (!path || !strcmp(path, "~"))
	{
		path = getenv_node(env, "HOME")->content;
		path = ft_strrchr(path, '=');
		path++;
	}
	res = chdir(path);
	node = getenv_node(env, "PWD");
	if(res < 0)
		printf("Error: %s\n", strerror(errno));
	else
	{
		buf = getcwd(NULL, PATH_MAX);
//		printf("->|%s|\n", buf);
		if (node && node->content)
			free(node->content);
//		printf("---content: %s\n", (char *)node->content);
//		node_old = getenv_node(env, "OLDPWD");
//		printf("lllllllllllllll\n");
//		if(node_old)
//			node_old->content = node->content;
		node->content = (void *)ft_strjoin("PWD=", buf);
		printf("%s\n", buf);
		free(buf);
	}
}
