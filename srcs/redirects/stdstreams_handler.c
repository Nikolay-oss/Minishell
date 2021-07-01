#include "minishell.h"

int	save_std_descriptors(t_stdstreams *stdstreams)
{
	stdstreams->std_in = dup(STDIN);
	if (stdstreams->std_in < 0)
		return (1);
	stdstreams->std_out = dup(STDOUT);
	if (stdstreams->std_out < 0)
		return (1);
	return (0);
}

int	revert_std_descriptors(t_stdstreams *stdstreams)
{
	if (dup2(stdstreams->std_in, STDIN) < 0)
		return (1);
	close(stdstreams->std_in);
	if (dup2(stdstreams->std_out, STDOUT) < 0)
		return (1);
	close(stdstreams->std_out);
	return (0);
}
