#include "minishell.h"

int	ft_pwd()
{
	char	*path;

	path = getcwd(NULL, PATH_MAX);
	if (path)
	{
		ft_putendl_fd(path, 1);
		free(path);
		return (0);
	}
	return (1);
}
