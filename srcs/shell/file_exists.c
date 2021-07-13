#include "minishell.h"
#include <sys/stat.h>

t_bool	file_exists(const char *filename)
{
	struct stat	buf;
	int			ret;

	ret = stat(filename, &buf);
	if (ret < 0)
		return (0);
	else
		return (1);
}
