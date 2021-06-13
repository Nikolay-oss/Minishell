#include "minishell.h"

void	ft_cd(char *path)
{
	int res;
	char buf[100];

	if (!path)
		printf("loool\n");
	res = chdir(path);
	if(res < 0)
		printf("Error: %s\n", strerror(errno));
	else
		printf("%s\n", getcwd(buf, 100));
}
