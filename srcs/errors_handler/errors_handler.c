#include "minishell.h"

void	print_error(int errorcode)
{
	char	*error;

	error = strerror(errorcode);
	write(2, error, ft_strlen(error));
	write(2, "\n", 1);
}
