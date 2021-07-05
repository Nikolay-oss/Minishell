#include "minishell.h"

void	print_error(char *str, int errorcode)
{
	char	*error;

	error = strerror(errorcode);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(error, 2);
}

void	command_not_found(char *str, int errorcode)
{
	if (errorcode == 127)
	{
		ft_putstr_fd(str, 2);
		ft_putendl_fd(": command not found", 2);
	}
}
