#include "minishell.h"
#include <fcntl.h>

int	save_std_descriptors(t_stdstreams *stdstreams)
{
	stdstreams->std_in = dup(STDIN_FILENO);
	if (stdstreams->std_in < 0)
		return (1);
	stdstreams->std_out = dup(STDOUT_FILENO);
	if (stdstreams->std_out < 0)
		return (1);
	return (0);
}

int	revert_std_descriptors(t_stdstreams *stdstreams)
{
	if (dup2(stdstreams->std_in, STDIN_FILENO) < 0)
		return (1);
	close(stdstreams->std_in);
	if (dup2(stdstreams->std_out, STDOUT_FILENO) < 0)
		return (1);
	close(stdstreams->std_out);
	return (0);
}

int	ft_redir(const char *filename, int o_flags, int s_flags, t_bool dir_type)
{
	int	fd;
	int	fd2;
	int	ret;

	ret = 0;
	fd = open(filename, o_flags, s_flags);
	if (fd < 0)
		return (1);
	if (dir_type)
		fd2 = STDOUT_FILENO;
	else
		fd2 = STDIN_FILENO;
	if (dup2(fd, fd2) < 0)
		ret = errno;
	close(fd);
	return (ret);
}
