#include "minishell.h"

void	ft_cd(t_list *env, char *path)
{
	int res;
	char *buf;

	if (!path || !strcmp(path, "~"))
		printf("loool\n");
	res = chdir(path);
	if(res < 0)
		printf("Error: %s\n", strerror(errno));
	else
	{
		buf = getcwd(NULL, 0);
		printf("->|%s|\n", buf);
//		getenv_node(env, "OLD_PWD")->content
//				= getenv_node(env, "PWD")->content;
//		free(getenv_node(env, "PWD")->content);
		printf("---content: %s", (char *)(getenv_node(env, "PWD")->content));
		(getenv_node(env, "PWD")->content) = (void *)buf;
		printf("%s\n", buf);
	}
}
